#ifndef LISKOV_HXX
#define LISKOV_HXX

namespace solid {
class Rectangle {
protected:
  int m_width, m_height;
public:
  explicit
  Rectangle(int width, int height)
    : m_width(width), m_height(height) {}

  virtual void set_width(int width) { Rectangle::m_width = width; }
  virtual void set_height(int height) { Rectangle::m_height = height; }

  int width() const { return Rectangle::m_width; }
  int height() const { return Rectangle::m_height; }

  int area() const { return Rectangle::m_width * Rectangle::m_height; }
};

class Square : public Rectangle {
public:
  explicit
  Square(int side) : Rectangle(side, side) {}

  void set_width(int width) override   { Rectangle::m_width = Rectangle::m_height = width; }
  void set_height(int height) override { Rectangle::m_width = Rectangle::m_height = height; }
};

int process(Rectangle &rect) {
    const auto w = rect.width();
    rect.set_height(10);

    return rect.area();
}

struct factory {
    static Rectangle create_rectangle(int w, int h) { return Rectangle(w,h); }
    static Rectangle create_square(int s)           { return Rectangle(s,s); }
};

}

#endif // LISKOV_HXX
