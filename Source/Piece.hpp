#pragma once

enum class Piece {
    PAWN,
    ROOK,
    KNIGHT,
    BISSHOP,
    QUEEN,
    KING
};

enum class Color {
    WHITE,
    BLACK,
};

struct ColoredPiece {
    [[nodiscard]] inline constexpr
    ColoredPiece(Piece piece, Color color)
            : m_piece(piece)
            , m_color(color) {
    }

    [[nodiscard]] inline constexpr Piece
    piece() const {
        return m_piece;
    }

    [[nodiscard]] inline constexpr Color
    color() const {
        return m_color;
    }

private:
    Piece m_piece;
    Color m_color;
};

[[nodiscard]] static constexpr int
pieceToSpriteIndex(Piece piece) {
    switch (piece) {
        case Piece::PAWN: return 5;
        case Piece::ROOK: return 4;
        case Piece::KNIGHT: return 3;
        case Piece::BISSHOP: return 2;
        case Piece::QUEEN: return 1;
        case Piece::KING: return 0;
    }

    return 0;
}
