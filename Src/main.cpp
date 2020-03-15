#include "Game.h"
#include "Landloard.h"
#include <algorithm>
void Show(const Landloard &l);

int main()
{
    //定义一个游戏对象
    Game game = Game();
    //生产1副牌
    game.Init();
    //打乱牌组
    const std::vector<Card::card> hand = game.Deal();
    //提取地主牌
    Landloard landloard = Landloard(hand);
    //玩家进入游戏阶段
    game._Start(hand);
    //抢地主
    for (int time = 0; time != 4; ++time)
    {
        //展示该轮次玩家手牌
        game._Show();
        //做出选择
        game._Grabe();
        //下一个
        game._Turn();
        //清空
        system("cls");
    }
    //地主牌显示
    landloard._Show();
    //任意键清空
    std::cin.get();
    //地主位置转化并给地主牌
    game.Landloard_Init(landloard._Get());
    //地主先开始
    game.Set_round(0);
    /* -- 测试 -- std::cout << landloard._Get().capacity << std::endl;*/
    //开始游戏 出牌
    while (!game.Get_Over())
    {
        //自身手牌显示
        game._Show();
        //出牌
        game.Show_Hand();
        //下一个
        game._Turn();
        //按键(临时)
        std::cin.get();
        //清空
        system("cls");
        //判断是否打完
        game.Is_Empty();
    }
    //显示结果
    game.Who_Win();
    //任意键退出
    std::cin.get();
}