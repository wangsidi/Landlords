#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Player
{
public:
    //友元函数
    friend void Show(const Player &p);
    //友元成员函数(让Game访问'手牌'和'玩家轮次')
    friend class Game;
    //设置牌类型(除大小王)
    typedef std::pair<std::string, int> card;
private:
    //手牌
    std::vector<card> hand_cards;
    //玩家轮次
    int _round;
public:
    //构造函数
    explicit Player() = default;
    explicit Player(const int &round):_round(round){}
    //初始化
    void Init(const std::vector<card> &cards);
    //排序
    void Sort();
};
//排序
inline void Player::Sort()
{
    //lambda
    std::sort(hand_cards.begin(), hand_cards.end(), [](const card &first, const card &second)->bool{return first.second < second.second;});
}
#endif