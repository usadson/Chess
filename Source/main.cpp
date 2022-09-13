#include <SFML/Graphics.hpp>
#include <iostream>

#include "CalculatePossibleMoves.hpp"
#include "Piece.hpp"

constexpr std::uint32_t windowSize = 600;
constexpr const sf::Vector2f tileSize(windowSize / 8.0f, windowSize / 8.0f);
constexpr const int pieceSpriteWidth = 200;
constexpr const int pieceSpriteHeight = 200;


std::array<std::array<std::optional<ColoredPiece>, 8>, 8> board{};
std::optional<sf::Vector2i> selectedTile{};
bool paintInvalidated = true;

static void
setupBoard() {
    board = {};
    selectedTile = std::nullopt;

    board[0][0] = ColoredPiece{Piece::ROOK, Color::WHITE};
    board[1][0] = ColoredPiece{Piece::KNIGHT, Color::WHITE};
    board[2][0] = ColoredPiece{Piece::BISSHOP, Color::WHITE};
    board[3][0] = ColoredPiece{Piece::QUEEN, Color::WHITE};
    board[4][0] = ColoredPiece{Piece::KING, Color::WHITE};
    board[5][0] = ColoredPiece{Piece::BISSHOP, Color::WHITE};
    board[6][0] = ColoredPiece{Piece::KNIGHT, Color::WHITE};
    board[7][0] = ColoredPiece{Piece::ROOK, Color::WHITE};

    board[0][7] = ColoredPiece{Piece::ROOK, Color::BLACK};
    board[1][7] = ColoredPiece{Piece::KNIGHT, Color::BLACK};
    board[2][7] = ColoredPiece{Piece::BISSHOP, Color::BLACK};
    board[3][7] = ColoredPiece{Piece::QUEEN, Color::BLACK};
    board[4][7] = ColoredPiece{Piece::KING, Color::BLACK};
    board[5][7] = ColoredPiece{Piece::BISSHOP, Color::BLACK};
    board[6][7] = ColoredPiece{Piece::KNIGHT, Color::BLACK};
    board[7][7] = ColoredPiece{Piece::ROOK, Color::BLACK};

    for (std::uint8_t i = 0; i < 8; ++i) {
        board[i][1] = ColoredPiece{Piece::PAWN, Color::WHITE};
        board[i][6] = ColoredPiece{Piece::PAWN, Color::BLACK};
    }
}


[[nodiscard]] constexpr bool
isMovePossible(const std::vector<sf::Vector2i> &possibleMoves, int x, int y) {
    return std::find(possibleMoves.begin(), possibleMoves.end(), sf::Vector2i{x, y}) != std::end(possibleMoves);
}

static void
handleMouseClick(std::vector<sf::Vector2i> &possibleMoves, const sf::Event &event) {
    const auto nextX = static_cast<int>(event.mouseButton.x / tileSize.x);
    const auto nextY = static_cast<int>(8 - event.mouseButton.y / tileSize.y);
    auto &possiblePieceAtNext = board[nextX][nextY];

    possibleMoves = calculatePossibleMoves();

    if (selectedTile.has_value()) {
        auto &possiblePieceAtOld = board[selectedTile->x][selectedTile->y];
        if (possiblePieceAtOld.has_value() && isMovePossible(possibleMoves, nextX, nextY)) {
            possiblePieceAtNext = possiblePieceAtOld;
            possiblePieceAtOld = std::nullopt;
            selectedTile = std::nullopt;
            possibleMoves = {};
            paintInvalidated = true;
            return;
        }
    }

    selectedTile = {nextX, nextY};
    possibleMoves = calculatePossibleMoves();
    paintInvalidated = true;
}

class App {
public:
    [[nodiscard]]
    App() noexcept
            : m_window(sf::VideoMode(sf::Vector2u(windowSize, windowSize)), "Scacchi") {
        if (!texture.loadFromFile("sprites.png")) {
            std::cout << "sprites.png not found\n";
            std::exit(EXIT_FAILURE);
        }
        sprite.setTexture(texture);
    }

    void
    run() noexcept {
        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();

                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Button::Left) {
                        handleMouseClick(m_possibleMoves, event);
                    }
                }
            }

            if (paintInvalidated) {
                paintInvalidated = false;
                drawBoard();
                m_window.display();
            }
        }
    }

    void
    drawBoard() {
        m_window.clear();

        for (std::uint8_t x = 0; x < 8; ++x) {
            for (std::uint8_t y = 0; y < 8; ++y) {
                const bool tileIsWhite = x % 2 == y % 2;

                if (selectedTile && selectedTile->x == x && selectedTile->y == y) {
                    m_rect.setFillColor(sf::Color::Green);
                } else if (tileIsWhite) {
                    m_rect.setFillColor(sf::Color::White);
                } else {
                    m_rect.setFillColor(sf::Color(128, 128, 128));
                }

                const sf::Vector2f position(x * tileSize.x, windowSize - (y + 1) * tileSize.y);

                m_rect.setPosition(position);
                m_window.draw(m_rect);

                const auto &piece = board[x][y];
                if (piece.has_value()) {
                    const auto offset = pieceToSpriteIndex(piece->piece());

                    sprite.setTextureRect(sf::IntRect({
                                                              offset * pieceSpriteWidth,
                                                              static_cast<int>(piece->color()) * pieceSpriteHeight
                                                      },
                                                      sf::Vector2i(pieceSpriteWidth, pieceSpriteHeight)));
                    sprite.setPosition(position);
                    sprite.setScale(sf::Vector2f(tileSize.x / pieceSpriteWidth, tileSize.y / pieceSpriteHeight));
                    m_window.draw(sprite);
                }

                if (std::find(m_possibleMoves.begin(), m_possibleMoves.end(), sf::Vector2i{x, y}) != std::end(m_possibleMoves)) {
                    if (auto pieceAtPossibleMove = board[x][y]; pieceAtPossibleMove.has_value() && pieceAtPossibleMove->color() == Color::BLACK)
                        circleShape.setFillColor(sf::Color(255, 255, 255, 128));
                    else
                        circleShape.setFillColor(sf::Color(100, 100, 100, 128));
                    circleShape.setPosition(sf::Vector2f{position.x + (tileSize.x - circleShape.getRadius() * 2) / 2, position.y + (tileSize.y - circleShape.getRadius() * 2) / 2});
                    m_window.draw(circleShape);
                }
            }
        }
    }

private:
    sf::RenderWindow m_window;
    std::vector<sf::Vector2i> m_possibleMoves;

    sf::RectangleShape m_rect{tileSize};
    sf::Texture texture;
    sf::Sprite sprite;
    sf::CircleShape circleShape{tileSize.x / 6};
};

int main() {
    setupBoard();

    App app;
    app.run();

    return 0;
}