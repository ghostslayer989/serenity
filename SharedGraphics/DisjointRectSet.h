#pragma once

#include <AK/Vector.h>
#include <SharedGraphics/Rect.h>

class DisjointRectSet {
public:
    DisjointRectSet() { }
    ~DisjointRectSet() { }
    DisjointRectSet(DisjointRectSet&& other) : m_rects(move(other.m_rects)) { }

    void add(const Rect&);

    void clear() { m_rects.clear(); }
    void clear_with_capacity() { m_rects.clear_with_capacity(); }
    const Vector<Rect>& rects() const { return m_rects; }

private:
    void shatter();

    Vector<Rect> m_rects;
};

