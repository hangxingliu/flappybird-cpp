# Flappybird Qt

## Threads

There has two threads in this program.

The first one is main thread (painting operation located in).
And the other one is calculation thread be named `GameStatusThread` and created by `GameStatus`.

There has a Timer in main thread be used for update game graphics timely created by `GameCanvas`.

## Collision (碰撞)

The principle of detecting collision as follows:

1. Get all border points from bird image after loaded. (exclude transparent points)
2. Then generate rotated `Collision` object base on original `Collision` object by method `rotate`.
3. The detect are points in rorated `Collision` object located in the area of pipe.

## Motion of bird

The bird will having a fixed upward velocity(速度) after you each click or press "spacebar".

And bird are falling freely (自由落体: freely falling body) in game. (v+=g (g=9.8))
