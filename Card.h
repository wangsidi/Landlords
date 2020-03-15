#ifndef CARD_H
#define CARD_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#define CARD_NUM 54
#define PLAYER_CARD_NUM 17

//设置牌
class Card
{
public:
    //友元
    friend void Show(const Card &c);
    //设置牌类型(除大小王)
    typedef std::pair<std::string, int> card;

private:
    //花色
    const std::vector<std::string> color = {"黑桃", "方块", "红桃", "草花"};
    //点数
    const std::vector<int> num = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    //牌组
    std::vector<card> cards;

public:
    //构造函数
    explicit Card() = default;
    //初始化
    void Init();
    //发牌
    std::vector<card> Deal() const;
};
#endif