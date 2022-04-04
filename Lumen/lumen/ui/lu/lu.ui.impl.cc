#include <lumen/ui/lui/lui.cc>

#include "lu.cc"

#include <indxs-ui>
#include <indxs>

namespace Lumen::UI
{
    fun GetUI2()->ui_ref
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
                m Fill = Color::RGBA(97, 255, 69, 100);
            };
            sub HStack mapn {
                sub BlurRect mapn {
                    m Width = 50;
                    m MinHeight = 50;
                    m Padding = { 10 };
                };
                sub BlurRect mapn {
                    m Width = 50;
                    m MinHeight = 50;
                };
            };
            sub BlurRect mapn {
                m Height = 30;
            };
            sub FillRect mapn {
                m Name = "X";
                m MaxSize = { AutoF, 50 };
                m Margin = { 5, 5 };
                m Padding = { 10, 0 };
                m Fill = Colors::Aqua;
            };

            sub SimpleButton mapn {
                m Height = 30;
                m Clicked += [](auto* e) {
                    Console.Log("Clicked!");
                };
            };
        };
        // clang-format enable

        return mapper.Make();
    }

    fun GetUI()->ui_ref
    {
        var u = INew<Index::UI::ScopedContainer>();
        var s = INew<Index::UI::HStack>();
        u->Attach(s);

        for (int i = 0; i < 10; i++)
        {
            s->Attach(GetUI2());
        }

        return u;
    }
}

#include <indxe-ui>
#include <indxe>