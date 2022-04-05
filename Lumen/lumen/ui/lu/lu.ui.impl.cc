#include <lumen/ui/lui/lui.cc>

#include "lu.cc"

#include <indxs-ui>
#include <indxs>

namespace Lumen::UI
{
    fun GetUI()->ui_ref
    {
        // clang-format disable
        var mapper = ScopedContainerMapper();
        m Name = "Container_ClickGUI";
        m Alignment = Align::Center;

        sub BlurRect mapmn;
        sub FillRect mapn {
            m Fill = Color::RGBA(15, 15, 15, 140);
        };

        sub VStack mapn {
            m Padding = { 6 };
            sub HStack mapn {
                m Height = 30;
                sub SimpleButton mapn {
                    m Name = "SimpleButton_Tab1";
                    m Width = 60;
                    m Margin = { 0, 0, 4, 0 };
                    m Clicked += [](auto* e) {
                        var switcher = e->SearchT<Switcher>(UIPath::From("Switcher"));
                        switcher->Index = 0;
                    };
                };
                sub SimpleButton mapn {
                    m Name = "SimpleButton_Tab2";
                    m Width = 60;
                    m Margin = { 0, 0, 4, 0 };
                    m Clicked += [](auto* e) {
                        var switcher = e->SearchT<Switcher>(UIPath::From("Switcher"));
                        switcher->Index = 1;
                    };
                };
                sub SimpleButton mapn {
                    m Name = "SimpleButton_Tab3";
                    m Width = 60;
                    m Margin = { 0, 0, 4, 0 };
                    m Clicked += [](auto* e) {
                        var switcher = e->SearchT<Switcher>(UIPath::From("Switcher"));
                        switcher->Index = 2;
                    };
                };
            };
            sub Switcher mapn {
                m Name = "Switcher";
                m MinWidth = 600;
                m Height = 350;
                m Padding = { 0, 80, 0, 0 };
                m Index = 1;

                sub Container, 0 mapn {
                    sub FillRect mapn {
                        m MaxSize = { 20, 20 };
                        m Fill = Colors::Red;
                    };
                };
                sub Container, 1 mapn {
                    sub FillRect mapn {
                        m MaxSize = { 20, 20 };
                        m Fill = Colors::Lime;
                    };
                };
                sub Container, 2 mapmn;
            };
        };

        return mapper.Make();
        // clang-format enable
    }
}

#include <indxe-ui>
#include <indxe>