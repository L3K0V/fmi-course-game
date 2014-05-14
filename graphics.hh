#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

class Game;

class Graphics {
    private:
        Game &game_;
    public:
        Graphics(Game &game)
        : game_(game) {}

        void update();
        void run();
        void stop();
        void render();
};

#endif // __GRAPHICS_H__
