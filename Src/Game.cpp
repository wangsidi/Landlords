#include "Game.h"

//玩家进入游戏阶段
void Game::_Start(const std::vector<Card::card> &hand)
{
    //定义玩家1、2、3以及定义并初始化地主牌
    Player player_01 = Player(0);
    Player player_02 = Player(1);
    Player player_03 = Player(2);
    //初始化玩家1、2、3
    player_01.Init(hand);
    player_02.Init(hand);
    player_03.Init(hand);
    //赋值
    players[0] = player_01;
    players[1] = player_02;
    players[2] = player_03;
}

//抢地主
void Game::_Grabe()
{
    //定义选择
    int ch;
    //选择
    std::clog << "1.抢地主 2.不抢    你的选择: " << std::ends;
    //获取选择
    if (std::cin >> ch)
        if (ch == 1)
            loandloard_round = _round;
    std::cin.clear();
    std::cin.sync();
}
//地主位置转化并给地主牌
void Game::Landloard_Init(std::vector<card> &card_three)
{
    //地主首位必须出牌
    must_out = true;
    //如果不是一号位抢到地主,与一号位交换
    if (loandloard_round)
    {
        //交换位置
        std::swap(players[loandloard_round], players[0]);
        //并拿三张牌
        std::copy(card_three.cbegin(), card_three.cend(), std::back_inserter(players[0].hand_cards));
        //清空容器缓存
        std::vector<card>().swap(card_three);
        //排序
        std::sort(players[0].hand_cards.begin(), players[0].hand_cards.end(), [](const card &first, const card &second) -> bool { return first.second < second.second; });
        //跳出
        return;
    }
    //并拿三张牌
    std::copy(card_three.begin(), card_three.end(), std::back_inserter(players[0].hand_cards));
    //清空容器缓存
    std::vector<card>().swap(card_three);
    //排序
    std::sort(players[0].hand_cards.begin(), players[0].hand_cards.end(), [](const card &first, const card &second) -> bool { return first.second < second.second; });
    //跳出
    return;
}
//谁赢了
void Game::Who_Win() const
{
    //确认为地主
    if (!who_win)
        std::clog << "地主胜利!" << std::endl;
    else
        std::clog << "农民胜利!" << std::endl;
}
//删牌(控制台获取牌型 -> 转化为点数 -> 遍历比较牌堆中牌点)
bool _del(const Card::card &card,const std::string &str)
{
    //变成int
    int temp = Game::sToint(str);
    //找到为true
    return temp == card.second;
}

//出牌
void Game::Show_Hand()
{
    //你出的牌组
    std::vector<std::string> out_card;
    //提示
    std::cout << "你的出牌(从小到大,空格间隔,以回车出牌<例:3 3 3\\n>): \n";
    //提取卡牌
    std::string temp;
    //ok？default ok
    bool is_ok = true;
    //correct
    bool is_correct = true;
    //如果出牌正确
    do
    {
        //优先判断不出计数是否达到2
        if (not_out_num == 2)
        {
            //这轮必须出牌,打头炮
            must_out = true;
            //桌面牌型刷新
            table_type = Game::card_type::empty;
            //桌面数量刷新
            table_num = 0;
        }
        //default
        is_ok = true;
        is_correct = true;
        out_type = Game::card_type::error;
        //clear
        std::vector<std::string>().swap(out_card);
        //直到回车停止
        while (std::cin.peek() != '\n' && std::cin >> temp)
        {
            //加入出牌卡组
            out_card.push_back(temp);
            //回车退出
            if (std::cin.peek() == '\n')
                break;
        }
        //回收回车
        std::cin.get();
        //位置
        auto t = players[_round].hand_cards.cbegin();
        //终止
        auto end = players[_round].hand_cards.cend();
        //如果出牌
        if (!out_card.empty())
        {
            //测试牌是否都存在
            for (int i = 0; i != out_card.size(); ++i)
            {
                //查找是否有这牌
                t = std::find_if(t, end, std::bind(_del, std::placeholders::_1, out_card[i]));
                //没找到
                if (t == end)
                {
                    //没找到,出牌错误
                    is_ok = false;
                    //跳出循环
                    break;
                }
                //找到后
                t++;
            }
            //如果牌都存在
            if (is_ok)
            {
                //牌型确认并返回牌型大小
                int temp = confirm_type(out_card);
                //如果牌型正确
                if (out_type != Game::card_type::error)
                {
                    //如果必须出牌,则说明桌面牌型为空,此为开头炮
                    if (must_out)
                    {
                        //刷新桌面牌型
                        table_type = out_type;
                        //刷新桌面牌数
                        table_num = out_card.size();
                        //刷新牌大小
                        table_max = temp;
                        //设false
                        must_out = false;
                        //计数清零
                        not_out_num = 0;
                        //true
                        //is_correct = true;
                    }
                    //如果可以是不出时出牌,说明是压牌
                    else
                    {
                        //桌面牌型数量一致且牌大(算进压炸弹)
                        if (out_type == table_type && table_num == out_card.size() && temp > table_max)
                        {
                            //计数清零
                            not_out_num = 0;
                            //刷新牌大小
                            table_max = temp;
                            //true
                            //is_correct = true;
                        }
                        //炸弹炸掉(牌面不是炸弹情况下)
                        else if(out_type == Game::card_type::boom)
                        {
                            //计数清零
                            not_out_num = 0;
                            //桌面刷新
                            table_type = Game::card_type::boom;
                            table_num = out_card.size();
                            table_max = temp;
                        }
                        else
                        {
                            is_correct = false;
                        }
                    }
                }
            }
        }
        //如果不出
        else
        {
            //设置为不出类型
            out_type = Game::card_type::empty;
            //计数
            not_out_num++;
        }
        //错误提示<--确认牌面有牌(不能三个人全部出,且地主开始必须出牌) <2020.3.13> -> 确认牌型正确 <2020.3.15>-> 确认牌型一致 <2020.3.15>-> 比较牌型大小 <2020.3.15>-> 设置炸弹王炸优先级 -->
    } while ((!is_ok && std::cout << "请重新出牌!" << std::endl) || (must_out && std::cout << "请出牌!" << std::endl) || (out_type == Game::card_type::error && std::cout << "出牌类型有误!" << std::endl) || (!is_correct && std::cout << "出牌类型不一致或牌太小!" << std::endl));
    //打出后手牌减少
    if (!out_card.empty())
    {
        //位置
        auto t = players[_round].hand_cards.cbegin();
        //终止
        auto end = players[_round].hand_cards.cend();
        //出牌(删手牌)
        for (int i = 0; i != out_card.size(); ++i)
        {
            //找到并删除
            t = std::find_if(t, end, std::bind(_del, std::placeholders::_1, out_card[i]));
            //删除指定迭代器
            players[_round].hand_cards.erase(t);
            //返回起始位置
            t = players[_round].hand_cards.begin();
        }
    }
    //否则提示"不出"
    else
    {
        //显示
        std::cout << "不出!" << std::endl;
    }
}