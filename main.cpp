#include <Novice.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>

const char kWindowTitle[] = "CSV Map Loader";

/// ===== 共有データ =====
std::vector<std::vector<int>> mapData;
bool isLoaded = false;
std::mutex mtx;

/// ===== CSV読み込み関数（別スレッドで動く）=====
void LoadCSV(const std::string& filename) {

    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::vector<std::vector<int>> tempMap;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<int> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stoi(cell));
        }

        tempMap.push_back(row);
    }

    /// 排他制御（スレッド安全）
    std::lock_guard<std::mutex> lock(mtx);
    mapData = tempMap;
    isLoaded = true;
}

/// ===== メイン =====
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    /// 読み込みスレッド開始
    std::thread loader(LoadCSV, "map.csv");
    loader.detach(); // 非同期化

    const int tileSize = 32;

    while (Novice::ProcessMessage() == 0) {

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        if (keys[DIK_ESCAPE]) break;

        Novice::BeginFrame();

        /// ===== 読み込み中表示 =====
        if (!isLoaded) {
            Novice::ScreenPrintf(500, 350, "Loading CSV...");
        } else {
            std::lock_guard<std::mutex> lock(mtx);

            for (int y = 0; y < mapData.size(); y++) {
                for (int x = 0; x < mapData[y].size(); x++) {

                    int tile = mapData[y][x];

                    unsigned int color = WHITE;

                    if (tile == 1) color = RED;
                    if (tile == 2) color = GREEN;
                    if (tile == 3) color = BLUE;

                    Novice::DrawBox(
                        x * tileSize,
                        y * tileSize,
                        tileSize,
                        tileSize,
                        0.0f,
                        color,
                        kFillModeSolid
                    );
                }
            }
        }

        Novice::EndFrame();
    }

    Novice::Finalize();
    return 0;
}
