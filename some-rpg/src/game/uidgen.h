#include <string>

using std::string;

typedef string UID;
// Generates only 7 characters, should have a low chance of collision
namespace ID 
{
    UID UIDGenPart()
    {
        string tmp = "";
        for (int i = 0; i < 7; ++i)
        {
            int temp = rand() % 62;
            if (temp > 51)
            {
                tmp += '0' + temp - 52;
            }
            else if (temp > 25)
            {
                tmp += 'a' + temp - 26;
            }
            else
            {
                tmp += 'A' + temp;
            }
        }
        return tmp;
    }

    UID UIDGen()
    {
        string part1, part2, part3;
        part1 = UIDGenPart();
        part2 = UIDGenPart();
        part3 = UIDGenPart();
        string temp =
            part1 + '-' +
            part2 + '-' +
            part3;
        return temp;
    }


}
