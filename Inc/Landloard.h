#ifndef LANDLOARD_H
#define LANDLOARD_H
#include <vector>
#include <iostream>

class Landloard
{
public:
    typedef std::pair<std::string, int> card;

private:
    std::vector<card> cards_three;

public:
    explicit Landloard() = default;
    explicit Landloard(const std::vector<card> &cards);
    std::vector<card>& _Get() { return cards_three; }
    virtual void _Show()const;
};
//初始化地主牌
inline Landloard::Landloard(const std::vector<card> &cards)
{
    //倒数三张
    int begin = 51;
    int end = 54;
    //获取三张地主牌
    for(int i = begin;i != end;++i)
        cards_three.push_back(cards[i]);
}
#endif