#include <SDL2/SDL.h>
#include "headers/snake.h"
#include "headers/const.h"

Snake::Snake()
{
    snake_blocks.push_back(XY(BLOCK_SIZE + BLOCK_SPEED, BLOCK_SIZE + BLOCK_SPEED));
}

void Snake::moveUP()
{
    // Change the speed of snake
    if (current_move != down)
    {
        speed.x = 0;
        speed.y = -BLOCK_SPEED;
        current_move = up;
    }
}
void Snake::moveDown()
{
    if (current_move != up)
    {
        speed.x = 0;
        speed.y = BLOCK_SPEED;
        current_move = down;
    }
}
void Snake::moveLeft()
{
    if (current_move != right)
    {
        speed.x = -BLOCK_SPEED;
        speed.y = 0;
        current_move = left;
    }
}
void Snake::moveRight()
{
    if (current_move != left)
    {
        speed.x = BLOCK_SPEED;
        speed.y = 0;
        current_move = right;
    }
}

void Snake::update()
{
    // Giving previous block of snake value of next block
    int size = snake_blocks.size();
    for (int i = size - 1; i > 0; i--)
    {
        snake_blocks[i] = snake_blocks[i - 1];
    }

    // head block chnaging to new value
    snake_blocks[0].x += speed.x;
    snake_blocks[0].y += speed.y;
}

bool Snake::checkCollision()
{
    // Check if snake has collided the itself
    XY snakeHead = getHead();

    for ( int i = 1; i < snake_blocks.size(); i++)
    {
        if ((snakeHead.x - snake_blocks[i].x) < BLOCK_SIZE &&
        (snakeHead.x - snake_blocks[i].x) > -BLOCK_SIZE &&
        (snakeHead.y - snake_blocks[i].y) < BLOCK_SIZE &&
        (snakeHead.y - snake_blocks[i].y) > -BLOCK_SIZE)
            return false;
    }

    // Checking for wall collision
    for (auto block : snake_blocks)
    {
        if (
            (block.x >= H + BLOCK_SIZE || block.x <= -(BLOCK_SIZE+BLOCK_SIZE/2)) ||
            (block.y >= W + BLOCK_SIZE || block.y <= -(BLOCK_SIZE+BLOCK_SIZE/2)))
        return false;
    }
    
    return true;
}

void Snake::show(SDL_Renderer *renderer)
{
    // Drawing head
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rectangle = {snake_blocks[0].x, snake_blocks[0].y, BLOCK_SIZE, BLOCK_SIZE};
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Drawing remaing blocks
    for (int i = 1; i < snake_blocks.size(); i++)
    {
        SDL_Rect rectangle = {snake_blocks[i].x, snake_blocks[i].y, BLOCK_SIZE, BLOCK_SIZE};
        SDL_RenderFillRect(renderer, &rectangle);
    }
    SDL_RenderPresent(renderer);
}

XY Snake::getHead()
{
    return snake_blocks[0];
}

void Snake::addNewBlock()
{
    snake_blocks.push_back(snake_blocks[0]);
}