#ifndef GAME_H
#define GAME_H
#include "Card.h"
#include "Player.h"
#include <functional>
#include <map>

class Game : public Card
{
public:
    enum card_type
    {
        error,
        empty,
        one,
        two,
        three,
        three_one,
        three_two,
        four_two,
        straight,
        join_pair,
        plain,
        plain_one,
        plain_two,
        boom
    };

private:
    //玩家集合
    Player players[3];
    //游戏是否结束
    bool is_over = false;
    //游戏玩家轮次
    int _round = 0;
    //出牌牌型
    card_type out_type = card_type::error;
    //桌面牌型
    card_type table_type = card_type::empty;
    //桌面牌型
    int table_num = 0;
    //桌面牌型大小
    int table_max = 0;
    //谁是地主
    int loandloard_round = 0;
    //不出次数
    int not_out_num = 0;
    //必须出牌
    bool must_out = false;
    //谁赢了
    int who_win = -1;

public:
    explicit Game() = default;
    //设置轮次
    void Set_round(const int &round) { _round = round; }
    //获取游戏是否结束
    const bool Get_Over() const { return is_over; }
    //谁赢了
    void Who_Win() const;
    //是否打完牌
    const bool Is_Empty();
    //玩家进入游戏阶段
    void _Start(const std::vector<Card::card> &hand);
    //打印
    virtual void _Show() const;
    //玩家轮转
    void _Turn();
    //抢地主
    void _Grabe();
    //地主位置转化并给地主牌
    void Landloard_Init(std::vector<card> &card_three);
    //出牌
    void Show_Hand();
    //string to int
    static const int sToint(const std::string &card);
    //牌型确认并返回牌大小
    int confirm_type(const std::vector<std::string> &out_cards);
};
//打印牌
inline void Game::_Show() const
{
    std::cout << "玩家" << players[_round]._round + 1 << ":\n";
    //计数
    int count = 1;
    //遍历打印
    for (auto i = players[_round].hand_cards.begin(); i != players[_round].hand_cards.end(); i++, count++)
    {
        //A打印
        if ((*i).second == 14)
            std::cout << (*i).first << 'A' << std::ends;
        //2打印
        else if ((*i).second == 15)
            std::cout << (*i).first << '2' << std::ends;
        //3-10正常打印
        else if ((*i).second >= 3 && (*i).second <= 10)
            std::cout << (*i).first << (*i).second << std::ends;
        //小王
        else if ((*i).second == 16)
            std::cout << (*i).first << std::ends;
        //大王
        else if ((*i).second == 17)
            std::cout << (*i).first << std::ends;
        //J、Q、K
        else
        {
            //临时存 J、Q、K
            const char ch[3] = {'J', 'Q', 'K'};
            //通过索引
            std::cout << (*i).first << ch[(*i).second - 11] << std::ends;
        }
        //满13张换行
        if (count % 13 == 0)
        {
            std::cout << "\n";
        }
    }
    //换行
    std::cout << std::endl;
}
//玩家轮转
inline void Game::_Turn()
{
    //到最后一个玩家轮转
    if (_round == 2)
        _round = 0;
    else
        _round++;
}
//是否打完牌
inline const bool Game::Is_Empty()
{
    for (int i = 0; i != 3; ++i)
        if (players[i].hand_cards.empty())
        {
            //记录胜利者
            who_win = i;
            //游戏结束
            is_over = true;

            return is_over;
        }

    return is_over;
}
//字符串转点数
inline const int Game::sToint(const std::string &card)
{
    //点数
    int num;
    //如果是3-10
    if (card == "3" || card == "4" || card == "5" || card == "6" || card == "7" || card == "8" || card == "9" || card == "10")
        num = std::stoi(card);
    //如果是J、Q、K、A、2
    if (card == "J")
        num = 11;
    if (card == "Q")
        num = 12;
    if (card == "K")
        num = 13;
    if (card == "A")
        num = 14;
    if (card == "2")
        num = 15;
    if (card == "小王")
        num = 16;
    if (card == "大王")
        num = 17;
    return num;
}
//牌型确认
inline int Game::confirm_type(const std::vector<std::string> &out_cards)
{
    //牌数
    int card_size = out_cards.size();
    //牌集转牌点集
    std::vector<int> card_nums(card_size);
    //存入牌点
    for (int i = 0; i != card_size; ++i)
        card_nums[i] = Game::sToint(out_cards[i]);
    //单张
    if (card_size == 1)
    {
        out_type = Game::card_type::one;
        return card_nums[0];
    }
    //两张
    if (card_size == 2)
    {
        //对子
        if (card_nums[0] == card_nums[1])
        {
            out_type = Game::card_type::two;
            return card_nums[0];
        }
        //王炸
        if (std::find(card_nums.begin(), card_nums.end(), 16) != card_nums.end() && std::find(card_nums.begin(), card_nums.end(), 17) != card_nums.end())
        {
            out_type = Game::card_type::boom;
            return card_nums[1];
        }
    }
    //三张
    if (card_size == 3)
        if (card_nums[0] == card_nums[1] && card_nums[1] == card_nums[2])
        {
            out_type = Game::card_type::three;
            return card_nums[0];
        }
    //四张
    if (card_size == 4)
    {
        //炸弹
        if (card_nums[0] == card_nums[1] && card_nums[1] == card_nums[2] && card_nums[2] == card_nums[3])
        {
            out_type = Game::card_type::boom;
            return card_nums[0];
        }
        //三带一
        if (card_nums[0] == card_nums[1] && card_nums[1] == card_nums[2] && card_nums[2] != card_nums[3])
        {
            out_type = Game::card_type::three_one;
            return card_nums[0];
        }
        if (card_nums[0] != card_nums[1] && card_nums[1] == card_nums[2] && card_nums[2] == card_nums[3])
        {
            out_type = Game::card_type::three_one;
            return card_nums[1];
        }
    }
    //五张以上
    if (card_size >= 5)
    {
        /* ----------------------三带二---------------------- */
        if (card_size == 5)
        {
            if (card_nums[0] == card_nums[1] && card_nums[1] != card_nums[2] && card_nums[2] == card_nums[3] && card_nums[3] == card_nums[4])
            {
                out_type = Game::card_type::three_two;
                return card_nums[2];
            }
            if (card_nums[0] == card_nums[1] && card_nums[1] == card_nums[2] && card_nums[2] != card_nums[3] && card_nums[3] == card_nums[4])
            {
                out_type = Game::card_type::three_two;
                return card_nums[0];
            }
        }
        /* -----------------------顺子----------------------- */
        {
            bool is_straight = true;

            for (int i = 0; i != card_size; ++i)
                //在3-A之间
                if (card_nums[i] < 3 || card_nums[i] > 14)
                {
                    is_straight = false;
                    break;
                }

            //如果依然是顺子
            if (is_straight)
                //牌点间隔永远为1的话
                for (int i = 0; i != card_size - 1;)
                {
                    //间隔为1
                    if ((card_nums[i + 1] - card_nums[i]) == 1)
                        i++;
                    //否则
                    else
                    {
                        is_straight = false;
                        break;
                    }
                }

            //最后还是顺子
            if (is_straight)
            {
                out_type = Game::card_type::straight;
                return card_nums[0];
            }
        }
        /* -----------------------连对----------------------- */
        //(3-A) 2不行(点数15)
        if (card_size >= 6 && card_size % 2 == 0 && card_nums.back() != 15)
        {
            //是否是顺子 334455
            bool is_pair = true;

            for (int i = 0; i != card_size; i += 2)
            {
                //第一张和第二张相同
                if (card_nums[i] == card_nums[i + 1])
                {
                    //如果还有牌
                    if (i + 2 != card_size)
                    {
                        //第二张与第三张相差1
                        if (card_nums[i + 2] - card_nums[i + 1] == 1)
                        {
                            continue;
                        }
                        //否则
                        else
                        {
                            is_pair = false;
                            break;
                        }
                    }
                }
                //否则
                else
                {
                    is_pair = false;
                    break;
                }
            }
            //如果是顺子
            if (is_pair)
            {
                out_type = Game::card_type::join_pair;
                return card_nums[0];
            }
        }
        /* -------------------------四带二----------------------- */
        if (card_size == 6)
        {
            //计数
            int card_count = 0;
            //能找到四个相同的即可 索引0、1、2中必有一个是四张的点数,否则不是四带二
            for (int i = 0; i != 3; ++i)
            {
                //重置计数
                card_count = 0;
                //操作卡牌点数
                int card_num = card_nums[i];
                //设置始末
                auto it = card_nums.begin();
                auto end = card_nums.end();
                //遍历查找
                while (1)
                {
                    it = std::find(it, end, card_num);
                    //找到了
                    if (it != end)
                    {
                        //计数+1
                        card_count++;
                        //找到的迭代器下一个位置
                        it++;
                    }
                    else
                    {
                        break;
                    }
                }
                //如果计数等于四
                if (card_count == 4)
                {
                    out_type = Game::card_type::four_two;
                    return card_num;
                }
            }
        }
        /* ------------------------飞机------------------------- */
        if (card_size >= 6 && card_size % 3 == 0)
        {
            bool is_plain = false;
            //几张三张牌
            int three_num = card_size / 3;
            //定义一个map
            std::map<int, int> temp;
            //存入map,方便操作
            for (const auto &item : card_nums)
            {
                //存入并计数
                temp[item]++;
            }
            //第一个三张
            std::pair<int, int> three_first;
            //找到第一个三张(有序)
            for (const auto &item : temp)
            {
                //计数为3
                if (item.second == 3)
                {
                    //记录
                    three_first = item;
                    //改true
                    is_plain = true;
                    //break
                    break;
                }
            }
            //通过有几个三张来判断,因为是连续的
            for (int i = 1; i != three_num; ++i)
            {
                //333444 (不能...222)
                if (temp[three_first.first + i] != 3 || three_first.first + i == 15)
                {
                    //改false
                    is_plain = false;
                    break;
                }
            }
            //如果true
            if (is_plain)
            {
                out_type = Game::card_type::plain;
                return three_first.first;
            }
        }
        /* ---------------------飞机(带一张)--------------------- */
        //8 33344456 34445556 34555666
        if (card_size >= 8 && card_size % 4 == 0)
        {
            bool is_plain_one = false;
            //几张三张牌
            int three_num = card_size / 4;
            //定义一个map
            std::map<int, int> temp;
            //存入map,方便操作
            for (const auto &item : card_nums)
            {
                //存入并计数
                temp[item]++;
            }
            //第一个三张
            std::pair<int, int> three_first;
            //找到第一个三张(有序)
            for (const auto &item : temp)
            {
                //计数为3
                if (item.second == 3)
                {
                    //记录
                    three_first = item;
                    //改true
                    is_plain_one = true;
                    //break
                    break;
                }
            }
            //通过有几个三张来判断,因为是连续的
            for (int i = 1; i != three_num; ++i)
            {
                //333444 (不能...222)
                if (temp[three_first.first + i] != 3 || three_first.first + i == 15)
                {
                    //改false
                    is_plain_one = false;
                    break;
                }
            }
            //如果true
            if (is_plain_one)
            {
                out_type = Game::card_type::plain_one;
                return three_first.first;
            }
        }
        /* ---------------------飞机(带两张)--------------------- */
        if (card_size >= 10 && card_size % 5 == 0)
        {
            bool is_plain_two = false;
            //几张三张牌
            int three_num = card_size / 5;
            //定义一个map
            std::map<int, int> temp;
            //存入map,方便操作
            for (const auto &item : card_nums)
            {
                //存入并计数
                temp[item]++;
            }
            //第一个三张
            std::pair<int, int> three_first;
            //找到第一个三张(有序)
            for (const auto &item : temp)
            {
                //计数为3
                if (item.second == 3)
                {
                    //记录
                    three_first = item;
                    //改true
                    is_plain_two = true;
                    //从map中删除
                    temp.erase(item.first);
                    //break
                    break;
                }
            }
            //通过有几个三张来判断,因为是连续的
            for (int i = 1; i != three_num; ++i)
            {
                //333444 (不能...222)
                if (temp[three_first.first + i] != 3 || three_first.first + i == 15)
                {
                    //改false
                    is_plain_two = false;
                    break;
                }
                //否则计数是3,从map中删除
                temp.erase(three_first.first + i);
            }
            //判断剩下的是否都是对子3+2一一对应
            auto it = temp.begin();
            for (int i = 0; i != temp.size(); ++i)
            {
                //不是对子
                if ((*it).second != 2)
                {
                    //改false
                    is_plain_two = false;
                    break;
                }
            }
            //如果true
            if (is_plain_two)
            {
                out_type = Game::card_type::plain_two;
                return three_first.first;
            }
        }
    }
    return -1;
}
#endif