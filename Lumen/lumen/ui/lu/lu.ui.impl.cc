#include <lumen/ui/lui/lui.cc>

#include "lu.cc"

#include <indxs-ui>
#include <indxs>

namespace Lumen::UI
{
    fun GetUI()->ui_ref
    {
        var mapper = ContainerMapper();

        // clang-format disable
        sub VStack mapn {
            m Name = "Stack1";
            m Alignment = Align::LeftTop;
            m Margin = { 20, 20 };
            m Width = 100;

            sub FillRect mapn {
                m Height = 40;
                m Fill = Color::RGB(97, 255, 69);
            };
//            sub HStack mapn {
//                sub FillRect mapn {
//                    m Width = 50;
//                    m MinHeight = 50;
//                    m Fill = Colors::Yellow;
//                    m Padding = { 10 };
//                };
//                sub FillRect mapn {
//                    m Width = 50;
//                    m MinHeight = 50;
//                    m Fill = Colors::Blue;
//                };
//            };
//            sub FillRect mapn {
//                m Height = 30;
//                m Fill = Colors::Red;
//            };
//            sub FillRect mapn {
//                m Name = "X";
//                m MaxSize = { AutoF, 50 };
//                m Margin = { 5, 5 };
//                m Padding = { 10, 0 };
//                m Fill = Colors::Aqua;
//            };
        };
        // clang-format enable

        return mapper.Make();
    }
}

#include <indxe-ui>
#include <indxe>