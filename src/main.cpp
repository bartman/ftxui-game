#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "array2d.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>

#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>

int main() {
    using namespace ftxui;

    auto screen = ScreenInteractive::FitComponent();

    const int board_width=200, board_height=100;
    auto board = Canvas(board_width, board_height);
    int block_width = 8, block_height = 4;
    int blocks_across = board_width / block_width;
    int blocks_heigh = 6;

    int paddle_x = board_width / 2;
    int paddle_width = 20;
    auto paddle_col = Color::White;

    struct xy { int x, y; };
    int ball_size = 2;
    xy ball_loc{ board_width / 2, board_height / 2 };
    xy ball_vec{ 1, 1 };

    struct block {
        int life;
    };
    Array2D<block, board_width, board_height> blocks;
    for (int r=0; r<blocks_heigh; r++) {
        for (int c=0; c<blocks_across; c++) {
            blocks(c,r).life = blocks_heigh - r;
        }
    }

    #if 0
    auto buttons = Container::Horizontal({
        Button("<<", [&] { }) | color(Color::Red),
        Button("==", [&] { }) | color(Color::Yellow),
        Button(">>", [&] { }) | color(Color::Green),
    });
    #endif

    auto quit_button = Button("Quit", [&] {
        screen.Exit();
    }, ButtonOption::Border());

    auto main_container = Container::Vertical({
        //buttons,
        quit_button,
    });

    auto component = Renderer(main_container, [&] {

        // draw blocks

        static const std::array<Color,7> row_colors = {
            Color::Black,
            Color::Violet,
            Color::Blue,
            Color::Green,
            Color::Yellow,
            Color::Orange3,
            Color::Red
        };

        auto DrawRectangle = [&](int x0, int y0, int x1, int y1, Color col) {
                board.DrawPointLine(x0,y0,x0,y1,col);
                board.DrawPointLine(x1,y0,x1,y1,col);
                board.DrawPointLine(x0,y0,x1,y0,col);
                board.DrawPointLine(x0,y1,x1,y1,col);
        };

        for (int r=0; r<blocks_heigh; r++) {
            for (int c=0; c<blocks_across; c++) {
                auto life = blocks(c,r).life;
                auto col = life < row_colors.size() ? row_colors[life] : Color::White;
                int x0 = c * block_width;
                int x1 = x0 + block_width - 1;
                int y0 = r * block_height;
                int y1 = y0 + block_height - 1;

                DrawRectangle(x0, y0, x1, y1, col);

                //std::stringstream ss;
                //ss << life;
                //board.DrawText(x0, y0, ss.str());
            }
        }

        // draw paddle

        {
            int x0 = paddle_x - (paddle_width/2);
            int x1 = paddle_x + (paddle_width/2);
            int y = board.height() - 4;

            board.DrawBlockLine(0,y,board.width(),y,Color::Black);
            board.DrawBlockLine(x0,y,x1,y,paddle_col);
        }

        // draw ball

        board.DrawPointCircleFilled(ball_loc.x, ball_loc.y, ball_size, Color::CyanLight);

        ball_loc.x += ball_vec.x;
        ball_loc.y += ball_vec.y;

        // return the frame

        return vbox({
            hbox({
                filler(),
                canvas(&board)
                | size(WIDTH, EQUAL, 100)
                | size(HEIGHT, EQUAL, 25),
                filler()
            }) | border,
            //buttons->Render() | border,
            filler(),
            hbox({
                filler(),
                quit_button->Render() | color(Color::Red),
            })
        });
    })
    | CatchEvent([&](Event event) {
            if (event.is_mouse()) {
                int x = (event.mouse().x - 1) * 2;
                int y = (event.mouse().y - 1) * 4;
                if (x >= 0 && x < board.width() && y >= 0 && y < board.height()) {
                    paddle_x = x;
                    paddle_col = Color::Blue;
                } else {
                    paddle_col = Color::Red;
                }

            } else if (event.is_character()) {
                switch (event.character()[0]) {
                    case 'a': case 'h':
                        paddle_x --;
                        break;
                    case 'd': case 'l':
                        paddle_x ++;
                        break;
                    case 'q':
                        screen.Exit();
                        break;
                }
            }
            return false;
        });

    screen.Loop(component);

    return 0;
}
