#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
    // ��������� ����
    const int windowWidth = 800;
    const int windowHeight = 600;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Ping pong");

    // ��������� �������
    const float racketWidth = 10;
    const float racketHeight = 100;
    const float racketSpeed = 300;

    RectangleShape leftRacket(Vector2f(racketWidth, racketHeight));
    leftRacket.setPosition(10, windowHeight / 2 - racketHeight / 2);
    leftRacket.setFillColor(Color::White);

    RectangleShape rightRacket(Vector2f(racketWidth, racketHeight));
    rightRacket.setPosition(windowWidth - 20, windowHeight / 2 - racketHeight / 2);
    rightRacket.setFillColor(Color::White);

    // ��������� ����
    const float ballRadius = 10;
    CircleShape ball(ballRadius);
    ball.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);
    ball.setFillColor(Color::Red);

    float ballSpeedX = 250;
    float ballSpeedY = 250;

    // ������� ����
    Clock clock;
    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // ��������� �������
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // �������� �������
        // ����� ������� (W/S)
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            leftRacket.move(0, -racketSpeed * dt);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            leftRacket.move(0, racketSpeed * dt);
        }

        // ������ ������� (���������)
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            rightRacket.move(0, -racketSpeed * dt);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            rightRacket.move(0, racketSpeed * dt);
        }

        // ����������� �������� �������
        if (leftRacket.getPosition().y < 0) {
            leftRacket.setPosition(leftRacket.getPosition().x, 0);
        }
        if (leftRacket.getPosition().y + racketHeight > windowHeight) {
            leftRacket.setPosition(leftRacket.getPosition().x, windowHeight - racketHeight);
        }

        if (rightRacket.getPosition().y < 0) {
            rightRacket.setPosition(rightRacket.getPosition().x, 0);
        }
        if (rightRacket.getPosition().y + racketHeight > windowHeight) {
            rightRacket.setPosition(rightRacket.getPosition().x, windowHeight - racketHeight);
        }

        // �������� ����
        ball.move(ballSpeedX * dt, ballSpeedY * dt);

        // ������ �� ������� � ������ ������
        if (ball.getPosition().y < 0 || ball.getPosition().y + 2 * ballRadius > windowHeight) {
            ballSpeedY = -ballSpeedY;
        }

        // ������ �� �������
        if (ball.getGlobalBounds().intersects(leftRacket.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightRacket.getGlobalBounds())) {
            ballSpeedX = -ballSpeedX;
        }

        // ����� �� ������� (��������) - ������ ������������� ���
        if (ball.getPosition().x < 0 || ball.getPosition().x > windowWidth) {
            ball.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);
            ballSpeedX = -ballSpeedX; // ����� �����������, ����� �� ��������� �� ������
        }

        window.clear();
        window.draw(leftRacket);
        window.draw(rightRacket);
        window.draw(ball);
        window.display();
    }

    return 0;
}



