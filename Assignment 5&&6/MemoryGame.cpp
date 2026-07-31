#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// cross platform
#define CLEAR_SCREEN() system("cls")

// pause function
void waitForEnter() {
    cin.clear();  // Clear any error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear buffer
    cout << "\nPress Enter to continue...";
    cin.get();  // Wait for Enter
}

// Classes
class Player {
private:
    string name;
    int highScoreEasy;
    int highScoreNormal;
    int highScoreHard;
    int gamesPlayed;
    int gamesWon;
    int bestStreak;
    int powerUps;

public:
    Player() : name("Guest"), highScoreEasy(0), highScoreNormal(0), 
               highScoreHard(0), gamesPlayed(0), gamesWon(0), 
               bestStreak(0), powerUps(0) {}
    
    Player(string n) : name(n), highScoreEasy(0), highScoreNormal(0), 
                        highScoreHard(0), gamesPlayed(0), gamesWon(0), 
                        bestStreak(0), powerUps(0) {}
    
    string getName() const { return name; }
    int getHighScore(string difficulty) const {
        if (difficulty == "Easy") return highScoreEasy;
        if (difficulty == "Hard") return highScoreHard;
        return highScoreNormal;
    }
    int getGamesPlayed() const { return gamesPlayed; }
    int getGamesWon() const { return gamesWon; }
    int getBestStreak() const { return bestStreak; }
    int getPowerUps() const { return powerUps; }
    
    void setHighScore(int score, string difficulty) {
        if (difficulty == "Easy" && score > highScoreEasy) 
            highScoreEasy = score;
        else if (difficulty == "Hard" && score > highScoreHard) 
            highScoreHard = score;
        else if (score > highScoreNormal) 
            highScoreNormal = score;
    }
    void incrementGamesPlayed() { gamesPlayed++; }
    void incrementGamesWon() { gamesWon++; }
    void setBestStreak(int streak) { 
        if (streak > bestStreak) bestStreak = streak; 
    }
    void addPowerUp() { powerUps++; }
    bool usePowerUp() { 
        if (powerUps > 0) { powerUps--; return true; }
        return false;
    }
    
    void saveToFile() {
        ofstream file("players.txt", ios::app);
        if (file.is_open()) {
            file << name << "," << highScoreEasy << "," << highScoreNormal << ","
                 << highScoreHard << "," << gamesPlayed << "," << gamesWon << ","
                 << bestStreak << "," << powerUps << "\n";
            file.close();
        }
    }
    
    static Player loadFromFile(string searchName) {
        ifstream file("players.txt");
        Player found;
        
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, scoreEasyStr, scoreNormalStr, scoreHardStr;
                string gamesStr, wonStr, streakStr, powerStr;
                
                getline(ss, name, ',');
                getline(ss, scoreEasyStr, ',');
                getline(ss, scoreNormalStr, ',');
                getline(ss, scoreHardStr, ',');
                getline(ss, gamesStr, ',');
                getline(ss, wonStr, ',');
                getline(ss, streakStr, ',');
                getline(ss, powerStr, ',');
                
                if (name == searchName) {
                    found.name = name;
                    found.highScoreEasy = stoi(scoreEasyStr);
                    found.highScoreNormal = stoi(scoreNormalStr);
                    found.highScoreHard = stoi(scoreHardStr);
                    found.gamesPlayed = stoi(gamesStr);
                    found.gamesWon = stoi(wonStr);
                    found.bestStreak = stoi(streakStr);
                    found.powerUps = stoi(powerStr);
                    break;
                }
            }
            file.close();
        }
        return found;
    }
    
    void updateFile() {
        ifstream file("players.txt");
        vector<string> lines;
        
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string fileName;
                getline(ss, fileName, ',');
                
                if (fileName == name) {
                    stringstream newLine;
                    newLine << name << "," << highScoreEasy << "," << highScoreNormal << ","
                           << highScoreHard << "," << gamesPlayed << "," << gamesWon << ","
                           << bestStreak << "," << powerUps;
                    lines.push_back(newLine.str());
                } else {
                    lines.push_back(line);
                }
            }
            file.close();
        }
        
        ofstream outFile("players.txt");
        if (outFile.is_open()) {
            for (string line : lines) {
                outFile << line << "\n";
            }
            outFile.close();
        }
    }
};

// lvl struct
struct Level {
    int digitCount;
    string description;
};

// functions
void showMainMenu();
void showPlayerMenu(Player& currentPlayer);
void startGame(Player& currentPlayer);
void viewLeaderboard();
bool viewPlayerStats(const Player& player);
string selectDifficulty();

// global variables
vector<Level> levels = {
    {3, "Easy - 3 digits"},
    {4, "Medium - 4 digits"},
    {5, "Hard - 5 digits"},
    {6, "Expert - 6 digits"},
    {7, "Master - 7 digits"}
};

// main function
int main() {
    srand(time(0));
    cout << "TEST BUILD 12345\n";
    
    cout << "=====================================\n";
    cout << "|   WELCOME TO MEMORY GAME          |\n";
    cout << "|   The Ultimate Memory Tester      |\n";
    cout << "=====================================\n\n";
    
    bool exitGame = false;
    
    while (!exitGame) {
        showMainMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                string name;
                cout << "Enter your name: ";
                getline(cin, name);
                
                Player player = Player::loadFromFile(name);
                if (player.getName() == "Guest") {
                    player = Player(name);
                    player.saveToFile();
                    cout << "\nNew player created! Welcome " << name << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                } else {
                    cout << "\nWelcome back " << name << "!\n";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
                
                showPlayerMenu(player);
                break;
            }
            case 2:
                viewLeaderboard();
                break;
            case 3:
                cout << "\nThanks for playing! Goodbye!\n";
                exitGame = true;
                break;
            default:
                cout << "Invalid choice. ";
                waitForEnter();
        }
    }
    return 0;
}

// difficulty
string selectDifficulty() {
    CLEAR_SCREEN();
    cout << "====================================\n";
    cout << "        SELECT DIFFICULTY          \n";
    cout << "====================================\n";
    cout << " 1. Easy (6 seconds to memorize)\n";
    cout << " 2. Normal (4 seconds)\n";
    cout << " 3. Hard (3 seconds) ⚡\n";
    cout << "====================================\n";
    cout << "Choose (1-3): ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch(choice) {
        case 1: return "Easy";
        case 3: return "Hard";
        default: return "Normal";
    }
}

// Menu function
void showMainMenu() {
    CLEAR_SCREEN();
    cout << "=====================================\n";
    cout << "           MAIN MENU               \n";
    cout << "=====================================\n";
    cout << " 1. Play Game (Login)\n";
    cout << " 2. View Leaderboard\n";
    cout << " 3. Exit\n";
    cout << "====================================\n";
    cout << "Choose (1-3): ";
}

void showPlayerMenu(Player& currentPlayer) {
    bool backToMain = false;
    
    while (!backToMain) {
        CLEAR_SCREEN();
        cout << "====================================\n";
        cout << "         PLAYER MENU               \n";
        cout << "====================================\n";
        cout << " Welcome, " << currentPlayer.getName() << "!\n";
        cout << "Easy High Score: " << currentPlayer.getHighScore("Easy") << "\n";
        cout << "Normal High Score: " << currentPlayer.getHighScore("Normal") << "\n";
        cout << "Hard High Score: " << currentPlayer.getHighScore("Hard") << "\n";
        cout << "Power-Ups: " << currentPlayer.getPowerUps() << "\n";
        cout << "Games Played: " << currentPlayer.getGamesPlayed() << "\n";
        cout << "Games Won: " << currentPlayer.getGamesWon() << "\n";
        cout << "Best Streak: " << currentPlayer.getBestStreak() << "\n";
        cout << "====================================\n";
        cout << " 1. Start Game\n";
        cout << " 2. View Your Stats\n";
        cout << " 3. Back to Main Menu\n";
        cout << "====================================\n";
        cout << "Choose (1-3): ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                startGame(currentPlayer);
                break;
            case 2:
               if (viewPlayerStats(currentPlayer)) {
                backToMain = true;
               }
               break;
            case 3:
                backToMain = true;
                break;
            default:
                cout << "Invalid choice. ";
                waitForEnter();
        }
    }
}

// Game function
void startGame(Player& currentPlayer) {
    // Select difficulty first
    string difficulty = selectDifficulty();
    
    int memorizeTime;
    if (difficulty == "Easy") memorizeTime = 6;
    else if (difficulty == "Hard") memorizeTime = 3;
    else memorizeTime = 4;
    
    int lives = 3;
    int currentLevel = 0;
    int score = 0;
    int streak = 0;
    bool gameActive = true;
    bool usedPowerUp = false;
    
    CLEAR_SCREEN();
    cout << "Starting " << difficulty << " mode with 3 lives!\n";
    cout << "You have " << memorizeTime << " seconds to memorize each set!\n";
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    while (currentLevel < 5 && lives > 0 && gameActive) {
        // Check for power-up
        if (!usedPowerUp && currentPlayer.getPowerUps() > 0 && lives == 1) {
            cout << "\n You have a Power-Up! Restore a life? (y/n): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'y' || choice == 'Y') {
                if (currentPlayer.usePowerUp()) {
                    lives++;
                    currentPlayer.updateFile();
                    cout << "Life restored! You have " << lives << " lives.\n";
                    usedPowerUp = true;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
            }
        }
        
        Level lvl = levels[currentLevel];
        vector<int> sequence;
        
        // Generate sequence
        for (int i = 0; i < lvl.digitCount; i++) {
            sequence.push_back(rand() % 9 + 1);
        }
        
        // show sequence
        CLEAR_SCREEN();
        cout << "====================================\n";
        cout << "  Level " << (currentLevel + 1) << "/5 - " << lvl.description << "\n";
        cout << "  Difficulty: " << difficulty << "  |  Time: " << memorizeTime << "s\n";
        cout << "  Lives: " << lives << "  |  Score: " << score << "  |  Streak: " << streak << "\n";
        cout << "====================================\n\n";
        cout << "MEMORIZE these numbers:\n\n";

        // Show one number at a time
        
        for (int num : sequence) {
         CLEAR_SCREEN();

         cout << "\n\n";
         cout << "              " << num << "\n";

         this_thread::sleep_for(chrono::milliseconds(800));
}

         // Remove the final number
         CLEAR_SCREEN();

        // Countdown
        cout << "Get ready to enter the numbers!\n\n";

        for (int i = 3; i > 0; i--) {
         cout << i << "... " << flush;
         this_thread::sleep_for(chrono::seconds(1));
}

         // Remove the countdown
         CLEAR_SCREEN();

         cout << "====================================\n";
         cout << "          TIME'S UP!               \n";
         cout << "====================================\n\n";
        
        // get player input
        cout << "Enter the " << lvl.digitCount << " numbers in order (space between):\n";
        bool correct = true;
        
        for (int i = 0; i < sequence.size(); i++) {
            int guess;
            cin >> guess;
            if (guess != sequence[i]) {
                correct = false;
                // Clear remaining input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        
        // check result
        if (correct) {
            int difficultyMultiplier = (difficulty == "Hard") ? 2 : (difficulty == "Easy") ? 1 : 1.5;
            int levelScore = 100 * (currentLevel + 1) * difficultyMultiplier;
            int bonus = streak * 10;
            int totalPoints = levelScore + bonus;
            score += totalPoints;
            streak++;
            
            cout << "\n Correct! +" << totalPoints << " points";
            if (bonus > 0) cout << " (Streak bonus: +" << bonus << ")";
            if (difficulty == "Hard") cout << " (Hard mode bonus!)";
            cout << "\n";
            
            currentLevel++;
            
            if (currentLevel == 5) {
                // win the game
                currentPlayer.incrementGamesPlayed();
                currentPlayer.incrementGamesWon();
                currentPlayer.setHighScore(score, difficulty);
                currentPlayer.setBestStreak(streak);
                currentPlayer.addPowerUp();
                currentPlayer.updateFile();
                
                CLEAR_SCREEN();
                cout << "   YOU DID IT!   \n";
                cout << "====================================\n";
                cout << "Difficulty: " << difficulty << "\n";
                cout << "Final Score: " << score << "\n";
                cout << "Best Streak: " << streak << "\n";
                cout << "Earned a Power-Up!\n";
                cout << "High Score (" << difficulty << "): " 
                     << currentPlayer.getHighScore(difficulty) << "\n";
                cout << "====================================\n";
                cout << "\n1. Play Again (Same Difficulty)\n";
                cout << "2. Quit to Player Menu\n";
                cout << "Choose: ";
                
                int winChoice;
                cin >> winChoice;
                cin.ignore(); // Clear the buffer
                
                if (winChoice == 1) {
                    // Reset everything and restart
                    lives = 3;
                    currentLevel = 0;
                    score = 0;
                    streak = 0;
                    usedPowerUp = false;
                    cout << "\n Starting new game...\n";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    // Continue the loop - will restart from level 0
                } else {
                    gameActive = false;
                }
            } else {
                cout << "\nNext level in 2 seconds...\n";
                this_thread::sleep_for(chrono::milliseconds(2000));
            }
        } else {
            lives--;
            streak = 0;
            cout << "\n Wrong! Life lost.\n";
            
            if (lives == 0) {
                currentPlayer.incrementGamesPlayed();
                currentPlayer.updateFile();
                
                CLEAR_SCREEN();
                cout << " GAME OVER!\n";
                cout << "====================================\n";
                cout << "Difficulty: " << difficulty << "\n";
                cout << "Score: " << score << "\n";
                cout << "Reached Level: " << (currentLevel + 1) << "/5\n";
                
                if (score > 0 && score > currentPlayer.getHighScore(difficulty)) {
                    currentPlayer.setHighScore(score, difficulty);
                    currentPlayer.updateFile();
                    cout << " NEW HIGH SCORE (" << difficulty << ")!\n";
                }
                cout << "====================================\n";
                cout << "\n1. Retry from Level 1\n";
                cout << "2. Quit to Player Menu\n";
                cout << "Choose: ";
                
                int retryChoice;
                cin >> retryChoice;
                cin.ignore(); // Clear the buffer
                
                if (retryChoice == 1) {
                    lives = 3;
                    currentLevel = 0;
                    score = 0;
                    streak = 0;
                    usedPowerUp = false;
                    cout << "\n Restarting game...\n";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                } else {
                    gameActive = false;
                }
            } else {
                cout << "\nRetrying Level " << (currentLevel + 1) << "...\n";
                this_thread::sleep_for(chrono::milliseconds(1500));
            }
        }
    }
}

// stats and board
void viewLeaderboard() {
    CLEAR_SCREEN();
    cout << "====================================\n";
    cout << "         LEADERBOARD               \n";
    cout << "====================================\n";
    
    ifstream file("players.txt");
    vector<pair<string, int>> easyPlayers, normalPlayers, hardPlayers;
    
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, scoreEasyStr, scoreNormalStr, scoreHardStr;
            getline(ss, name, ',');
            getline(ss, scoreEasyStr, ',');
            getline(ss, scoreNormalStr, ',');
            getline(ss, scoreHardStr, ',');
            
            easyPlayers.push_back({name, stoi(scoreEasyStr)});
            normalPlayers.push_back({name, stoi(scoreNormalStr)});
            hardPlayers.push_back({name, stoi(scoreHardStr)});
        }
        file.close();
    }
    
    // Sort each category
    sort(easyPlayers.begin(), easyPlayers.end(), 
         [](auto &a, auto &b) { return a.second > b.second; });
    sort(normalPlayers.begin(), normalPlayers.end(), 
         [](auto &a, auto &b) { return a.second > b.second; });
    sort(hardPlayers.begin(), hardPlayers.end(), 
         [](auto &a, auto &b) { return a.second > b.second; });
    
    // Display all three leaderboards
    vector<pair<string, vector<pair<string, int>>>> categories = {
        {"EASY (6s)", easyPlayers},
        {"NORMAL (4s)", normalPlayers},
        {"HARD (3s)", hardPlayers}
    };
    
    for (auto &cat : categories) {
        cout << "\n --- " << cat.first << " ---\n";
        bool hasScores = false;
        for (auto &p : cat.second) {
            if (p.second > 0) hasScores = true;
        }
        
        if (!hasScores) {
            cout << "    No scores yet!\n";
        } else {
            cout << "    Rank  Player                Score\n";
            int rank = 1;
            for (int i = 0; i < min(5, (int)cat.second.size()); i++) {
                if (cat.second[i].second > 0) {
                    cout << "    #" << setw(3) << rank++ << "  "
                         << setw(20) << left << cat.second[i].first
                         << right << setw(8) << cat.second[i].second << "\n";
                }
            }
        }
    }
    
    waitForEnter();
}

bool viewPlayerStats(const Player& player) { 
    CLEAR_SCREEN();
    cout << "====================================\n";
    cout << "         YOUR STATS              \n";
    cout << "====================================\n";
    cout << "  Name: " << player.getName() << "\n";
    cout << "  Easy High Score: " << player.getHighScore("Easy") << "\n";
    cout << "  Normal High Score: " << player.getHighScore("Normal") << "\n";
    cout << "  Hard High Score: " << player.getHighScore("Hard") << "\n";
    cout << "  Games Played: " << player.getGamesPlayed() << "\n";
    cout << "  Games Won: " << player.getGamesWon() << "\n";
    
    double winRate = (player.getGamesPlayed() > 0) ? 
                     (double)player.getGamesWon() / player.getGamesPlayed() * 100 : 0;
    cout << "  Win Rate: " << fixed << setprecision(1) << winRate << "%\n";
    cout << "  Best Streak: " << player.getBestStreak() << "\n";
    cout << "  Power-Ups: " << player.getPowerUps() << "\n";
    cout << "====================================\n";
    cout << "\n====================================\n";
    cout << "1. Back to Player Menu\n";
    cout << "2. Back to Main Menu\n";
    cout << "Choose: ";

    int choice;
    cin >> choice;
    cin.ignore();

    return choice == 2;
}