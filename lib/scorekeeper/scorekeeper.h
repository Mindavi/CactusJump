#ifndef LIB_SCOREKEEPER_SCOREKEEPER_H_
#define LIB_SCOREKEEPER_SCOREKEEPER_H_

#include <cinttypes>
#include <array>
#include <FS.h>

template<int N>
class ScoreKeeper {
 public:
    std::array<uint32_t, N> Scores() {
        Load();
        return m_high_scores;
    }
    // Returns true when the high score is placed somewhere in the list of high scores,
    // false when it's not higher than any of the old scores
    bool TryInsert(uint32_t new_score) {
        Load();
        bool result = Insertion(new_score);
        Store();
        return result;
    }

 private:
    const char *filename = "highscores.txt";
    bool Insertion(uint32_t new_score) {
        for (auto& score : m_high_scores) {
            if (new_score > score) {
                auto old_score = score;
                score = new_score;
                Insertion(old_score);
                return true;
            }
        }
        return false;
    }
    std::array<uint32_t, N> m_high_scores;
    void Store() {
        File score_file = SPIFFS.open(filename, "w");
        if (!score_file) {
            return;
        }
        for (const auto &score : m_high_scores) {
            score_file.println(score);
        }
        score_file.close();
    }
    void Load() {
        File score_file = SPIFFS.open(filename, "r");
        if (!score_file) {
            return;
        }
        for (auto &score : m_high_scores) {
            score = score_file.readStringUntil('\n').toInt();
        }
        score_file.close();
    }
};

using ScoreKeeperDefault = ScoreKeeper<5>;

#endif  // LIB_SCOREKEEPER_SCOREKEEPER_H_
