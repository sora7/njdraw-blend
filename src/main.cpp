#include <blend2d.h>
#include <SDL.h>

#define POINTS_COUNT 4

static SDL_Point points[POINTS_COUNT] = {
    {320, 200},
    {300, 240},
    {340, 240},
    {320, 200}
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void test_blend()
{
    BLImage img(480, 480, BL_FORMAT_PRGB32);

    // Attach a rendering context into `img`.
    BLContext ctx(img);

    // Clear the image.
    ctx.setCompOp(BL_COMP_OP_SRC_COPY);
    ctx.fillAll();

    // Fill some path.
    BLPath path;
    path.moveTo(26, 31);
    path.cubicTo(642, 132, 587, -136, 25, 464);
    path.cubicTo(882, 404, 144, 267, 27, 31);

    ctx.setCompOp(BL_COMP_OP_SRC_OVER);
    ctx.setFillStyle(BLRgba32(0xFFFFFFFF));
    ctx.fillPath(path);

    // Detach the rendering context from `img`.
    ctx.end();

    // Let's use some built-in codecs provided by Blend2D.
    BLImageCodec codec;
    codec.findByName("BMP");
    img.writeToFile("bl-getting-started-1.bmp", codec);
}

void test_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                        0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    test_blend();
    test_sdl();
    return 0;
}
