#include "Card.h"

//初始化
void Card::Init()
{
    //设置牌组(3-K)
    for (auto i = color.begin(); i != color.end(); i++)
        for (auto j = num.begin(); j != num.end(); j++)
        {
            //定义一个临时值
            card temp;
            //赋花色
            temp.first = *i;
            //赋牌点
            temp.second = *j;
            //加入牌组
            cards.push_back(temp);
        }
    //设置 A、2
    //四个花色
    for (auto i = color.begin(); i != color.end(); i++)
        //两张牌
        for (int time = 0; time != 2; ++time)
        {
            //定义一个临时值
            card temp;
            //赋花色
            temp.first = *i;
            //赋牌点
            temp.second = 14 + time;
            //加入牌组
            cards.push_back(temp);
        }

    //设置大小王
    card temp;

    //赋小王名
    temp.first = "小王";
    //赋值
    temp.second = 16;
    //加入牌组
    cards.push_back(temp);

    //赋大王名
    temp.first = "大王";
    //赋值
    temp.second = 17;
    //加入牌组
    cards.push_back(temp);
}

//发牌
std::vector<Card::card> Card::Deal() const
{
    //随机索引集
    int index[CARD_NUM];
    //设置卡牌
    std::vector<Card::card> cards_hand;
    //随即种子
    srand(time(NULL));
    //随即索引存入
    for (int i = 0; i != CARD_NUM;)
    {
        //是否添加
        bool is_add = true;
        //随机索引
        int card_index = rand() % CARD_NUM;
        //如果有了,下一循环(存入i个遍历i个即可)
        for (int j = 0; j != i; ++j)
            if (index[j] == card_index)
            {
                is_add = false;
                break;
            }
        //存入
        if (is_add)
            index[i++] = card_index;
        //否则
        else
            //下一循环
            is_add = true;
    }
    //通过随机索引获取牌组
    for (int i = 0; i != CARD_NUM; ++i)
        //存入手牌集
        cards_hand.push_back(cards[index[i]]);
    //返回结果
    return cards_hand;
}
