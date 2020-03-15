#include "Player.h"

//初始化玩家牌并打印
void Player::Init(const std::vector<card> &cards)
{
    //定义起始索引和末索引
    int begin, end;
    //玩家 1、2、3
    if (_round >= 0 && _round <= 2)
    {
        //设置起始索引
        begin = 17 * _round;
        //设置末索引
        end = begin + 17;
    }
    else
        return;
    //加入相应牌集
    for (int i = begin; i != end; ++i)
        hand_cards.push_back(cards[i]);
    //排序
    std::sort(hand_cards.begin(), hand_cards.end(), [](const card &first, const card &second) -> bool { return first.second < second.second; });
}