#include "CalculatePossibleMoves.hpp"
#include "Piece.hpp"

extern std::array<std::array<std::optional<ColoredPiece>, 8>, 8> board;
extern std::optional<sf::Vector2i> selectedTile;

std::vector<sf::Vector2i>
calculatePossibleMovesForPawn(const ColoredPiece &pawnPiece) {
    if (selectedTile->y == 7)
        return {};

    std::vector<sf::Vector2i> possibleMoves{};

    if (!board[selectedTile->x][selectedTile->y + 1].has_value())
        possibleMoves.emplace_back(selectedTile->x, selectedTile->y + 1);

    if (selectedTile->x >= 1) {
        const auto &hittablePiece = board[selectedTile->x - 1][selectedTile->y + 1];
        if (hittablePiece.has_value() && hittablePiece->color() != pawnPiece.color())
            possibleMoves.emplace_back(selectedTile->x - 1, selectedTile->y + 1);
    }

    if (selectedTile->x <= 6) {
        const auto &hittablePiece = board[selectedTile->x + 1][selectedTile->y + 1];
        if (hittablePiece.has_value() && hittablePiece->color() != pawnPiece.color())
            possibleMoves.emplace_back(selectedTile->x + 1, selectedTile->y + 1);
    }

    return possibleMoves;
}

std::vector<sf::Vector2i>
calculatePossibleMovesForKnight(const ColoredPiece &piece) {
    std::array<sf::Vector2i, 8> movesToCheck {
            sf::Vector2i{selectedTile->x + 2, selectedTile->y - 1},
            sf::Vector2i{selectedTile->x + 2, selectedTile->y + 1},
            sf::Vector2i{selectedTile->x - 2, selectedTile->y - 1},
            sf::Vector2i{selectedTile->x - 2, selectedTile->y + 1},
            sf::Vector2i{selectedTile->x + 1, selectedTile->y + 2},
            sf::Vector2i{selectedTile->x - 1, selectedTile->y + 2},
            sf::Vector2i{selectedTile->x + 1, selectedTile->y - 2},
            sf::Vector2i{selectedTile->x - 1, selectedTile->y - 2},
    };


    std::vector<sf::Vector2i> possibleMoves{};

    for (const auto &moveToCheck : movesToCheck) {
        if (moveToCheck.x < 0 || moveToCheck.x > 7 || moveToCheck.y < 0 || moveToCheck.y > 7)
            continue;

        const auto &pieceAtThatPosition = board[moveToCheck.x][moveToCheck.y];
        if (!pieceAtThatPosition.has_value() || pieceAtThatPosition->color() != piece.color())
            possibleMoves.push_back(moveToCheck);
    }

    return possibleMoves;
}

[[nodiscard]] static std::vector<sf::Vector2i>
calculatePossibleMovesForRook(const ColoredPiece &piece) {
    std::vector<sf::Vector2i> possibleMoves{};

    auto check = [&] (int x, int y) -> bool {
        const auto &pieceAtPosition = board[x][y];
        if (pieceAtPosition.has_value()) {
            if (pieceAtPosition->color() != piece.color())
                possibleMoves.emplace_back(x, y);
            return false;
        }

        possibleMoves.emplace_back(x, y);
        return true;
    };

    if (selectedTile->x < 7) {
        for (int x = selectedTile->x + 1; x < 8; ++x) {
            if (!check(x, selectedTile->y))
                break;
        }
    }

    if (selectedTile->x > 0) {
        for (int x = selectedTile->x - 1; x >= 0; --x) {
            if (!check(x, selectedTile->y))
                break;
        }
    }


    if (selectedTile->y < 7) {
        for (int y = selectedTile->y + 1; y < 8; ++y) {
            if (!check(selectedTile->x, y))
                break;
        }
    }

    if (selectedTile->y > 0) {
        for (int y = selectedTile->y - 1; y >= 0; --y) {
            if (!check(selectedTile->x, y))
                break;
        }
    }

    return possibleMoves;
}

std::vector<sf::Vector2i>
calculatePossibleMoves() {
    if (!selectedTile.has_value())
        return {};

    const auto &piece = board[selectedTile->x][selectedTile->y];
    if (!piece.has_value())
        return {};

    std::vector<sf::Vector2i> possibleMoves{};

    switch (piece->piece()) {
        case Piece::PAWN:
            return calculatePossibleMovesForPawn(piece.value());
        case Piece::ROOK:
            return calculatePossibleMovesForRook(piece.value());
        case Piece::KNIGHT:
            return calculatePossibleMovesForKnight(piece.value());
        default:
            break;
    }

    return possibleMoves;
}


