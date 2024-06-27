#include <stdio.h>

// Размер поля
const int WIDTH = 80;
const int HEIGHT = 25;

// Символы для использования
const char BALL_SYMB = 'o';
const char GRID_SYMB = '#';
const char RACKET1_SYMB = ']';
const char RACKET2_SYMB = '[';

// Начальные координаты сетки
const int GRID_COORD = 40;

// Начальные координаты ракетки 1
const int START_X_RACKET_1 = 10;
const int START_Y_RACKET_1 = 13;

// Начальные координаты ракетки 2
const int START_X_RACKET_2 = 70;
const int START_Y_RACKET_2 = 13;

// Начальные координаты мяча
const int START_X_BALL = 39;
const int START_Y_BALL = 13;

// Скорость мяча и ракетки
const int BALL_SPEED = 1;
const int RACKET_SPEED = 1;

// Объявление всех функций
void window_display(int, int, int, int, int, int);
void rocket_movement(int*, int*, char);
void ball_choose_winner(int*, int*, int*);
void ball_movement(int*, int*, int*, int*, int, int, int, int);
void score_count(int*, int*, int*);
void draw_score(int, int);
void winner_srceen(int*, int*);

// MAIN
int main() {
    // Координаты ракетки 1
    int x1 = START_X_RACKET_1, y1 = START_Y_RACKET_1;
    // Координаты ракетки 2
    int x2 = START_X_RACKET_2, y2 = START_Y_RACKET_2;
    // Координаты мяча
    int x_ball = START_X_BALL, y_ball = START_Y_BALL;

    // Переменны для счета игроков
    int first = 0;
    int second = 0;
    // Выбор победителя
    int choose_winner = 0;

    // Переменная отвечающая за угол полета мяча
    int view = 3;

    // view
    // 1 - x⬆️y⬇️
    // 2 - x⬆️y⬆️
    // 3 - x⬇️y⬆️
    // 4 - x⬇️y⬇️

    // Первый вывод экрана
    window_display(x1, y1, x2, y2, x_ball, y_ball);

    // Цикл до получения 21 очка одним из игроков
    while (first < 21 && second < 21) {
        // Подсчет и отрисовка SCORE
        score_count(&first, &second, &choose_winner);
        draw_score(first, second);

        // Получение символа на вход и перемещение ракеток
        char symb = getchar();
        rocket_movement(&y1, &y2, symb);

        // Перемещение мяча
        ball_movement(&x_ball, &y_ball, &view, &choose_winner, x1, y1, x2, y2);

        // Отрисовка экрана
        window_display(x1, y1, x2, y2, x_ball, y_ball);
    }
    // Конечная отрисовка экрана
    winner_srceen(&first, &second);
    draw_score(first, second);
}

// Фунцкция отрисовки всего поля и объектов
void window_display(int x1, int y1, int x2, int y2, int x_ball, int y_ball) {
    // Рисует поле
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            // Верхняя и нижняя грань
            if (i == 0 || i == HEIGHT - 1) {
                printf("=");
            }
            // Сетка
            else if (j == GRID_COORD || j == GRID_COORD - 1) {
                printf("%c", GRID_SYMB);
            }
            // Ракетка 1
            else if (j == x1 && (i == y1 - 1 || i == y1 || i == y1 + 1)) {
                printf("%c", RACKET1_SYMB);
            }
            // Ракетка 2
            else if (j == x2 && (i == y2 - 1 || i == y2 || i == y2 + 1)) {
                printf("%c", RACKET2_SYMB);
            }
            // Мяч
            else if (j == x_ball && i == y_ball) {
                printf("%c", BALL_SYMB);
            }
            // Пустое пространство
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

// Функция для передвижения ракеток (проверяет выход за границу карты)
void rocket_movement(int* y1, int* y2, char symb) {
    if (symb == 'a' && *y1 != 2)
        *y1 -= RACKET_SPEED;

    else if (symb == 'z' && *y1 != HEIGHT - 3)
        *y1 += RACKET_SPEED;

    else if (symb == 'k' && *y2 != 2)
        *y2 -= RACKET_SPEED;

    else if (symb == 'm' && *y2 != HEIGHT - 3)
        *y2 += RACKET_SPEED;
}

// Функция для выбора победителя и телепорта на сетку
void ball_choose_winner(int* x, int* y, int* choose_winner) {
    // Выиграл правый
    if (*x <= 0) {
        *choose_winner = 2;
        *x = START_X_BALL;
        *y = START_Y_BALL;
    }
    // Выиграл левый
    else if (*x >= WIDTH - 1) {
        *choose_winner = 1;
        *x = START_X_BALL;
        *y = START_Y_BALL;
    }
}

// view
// 1 - x⬆️y⬇️
// 2 - x⬆️y⬆️
// 3 - x⬇️y⬆️
// 4 - x⬇️y⬇️

// Функция, отвечающая за передвижение мяча
void ball_movement(int* x, int* y, int* view, int* choose_winner, int x_racket1, int y_racket1, int x_racket2,
                   int y_racket2) {
    // Вызов функции для выбора победителя, а также телепорта на сетку
    ball_choose_winner(x, y, choose_winner);

    // Смена траектории при ударе

    // ударился об левую ракетку
    if (*x == x_racket1 + 1 && (*y == y_racket1 || *y == y_racket1 + 1 || *y == y_racket1 - 1)) {
        if (*view == 4) {
            *view = 1;
        } else if (*view == 3) {
            *view = 2;
        }
    }
    // ударился об правую ракетку
    else if (*x == x_racket2 - 1 && (*y == y_racket2 || *y == y_racket2 + 1 || *y == y_racket2 - 1)) {
        // право-вниз на лево-вниз
        if (*view == 2) {
            *view = 3;
        }
        // право-вверх на лево-вверх
        else if (*view == 1) {
            *view = 4;
        }
    }
    // ударился об потолок
    else if (*y <= 0) {
        // право-вверх на право-вниз
        if (*view == 1) *view = 2;
        // лево-вверх на лево-вниз
        else if (*view == 4)
            *view = 3;
    }
    // ударился об пол
    else if (*y >= HEIGHT - 1) {
        // право-вниз на право-вверх
        if (*view == 2) {
            *view = 1;
        }
        // лево-вниз на лево-вверх
        else if (*view == 3) {
            *view = 4;
        }
    }

    // Перемещение мяча в зависимости от траектории

    // право-вверх
    if (*view == 1) {
        *x += BALL_SPEED;
        *y -= BALL_SPEED;
    }
    // право-вниз
    else if (*view == 2) {
        *x += BALL_SPEED;
        *y += BALL_SPEED;
    }
    // лево-вниз
    else if (*view == 3) {
        *x -= BALL_SPEED;
        *y += BALL_SPEED;
    }
    // лево-вверх
    else if (*view == 4) {
        *x -= BALL_SPEED;
        *y -= BALL_SPEED;
    }
}

// Функция для подсчета очков (увеличивает выигравшему игроку на 1)
void score_count(int* first, int* second, int* choose_winner) {
    if (*choose_winner == 1)
        *first += 1;
    else if (*choose_winner == 2)
        *second += 1;
    *choose_winner = 0;
}

// Отрисовка SCORE
void draw_score(int first, int second) {
    // Выравнивание по середине
    for (int i = 0; i < GRID_COORD - 6; ++i) printf(" ");
    printf("SCORE: %d/%d\n", first, second);
}

// Функция для отрисовки кубка победителя
void winner_srceen(int* first, int* second) {
    if (*first > *second) {
        printf(
            "\n \
                                    WINNER\n \
                                   ________\n \
                                  |        |\n \
                                 (| PLAYER |)\n \
                                  |  # 1   |\n \
                                   \\      / \n \
                                    `----' \n \
                                    _|__|_\n\n");
    } else {
        printf(
            "\n \
                                    WINNER\n \
                                   ________\n \
                                  |        |\n \
                                 (| PLAYER |)\n \
                                  |  # 2   |\n \
                                   \\      / \n \
                                    `----' \n \
                                    _|__|_\n\n");
    }
}
