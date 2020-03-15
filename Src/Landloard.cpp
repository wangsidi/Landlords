#include "Landloard.h"

void Landloard::_Show()const
{
    std::cout << "地主牌:\n";
    //遍历打印
    for (auto i = cards_three.begin(); i != cards_three.end(); i++)
    {
        //A打印
        if ((*i).second == 14)
            std::cout << (*i).first << 'A' << std::ends;
        //2打印
        else if ((*i).second == 15)
            std::cout << (*i).first << '2' << std::ends;
        //2-10正常打印
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
    }
    //换行
    std::cout << std::endl;
}