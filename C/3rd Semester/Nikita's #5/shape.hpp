#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>


class Shape {
public:
    Shape(int num_of_params, bool _shown=false):
        param(std::vector<float>(num_of_params)),
        param_name(std::vector<std::string>(num_of_params)),
        shown(_shown) {};
    virtual ~Shape() {};

    virtual void display(sf::RenderWindow& w) = 0;
    virtual void set_pos(int _x, int _y) = 0;
    virtual void move(int dx, int dy) {
        set_pos(x + dx, y + dy);
    };

    virtual bool isShown() const {return shown;}
    virtual void show() {
        shown = true;

    }
    virtual void hide() {
        shown = false;

    }

    virtual void print_params() {
        std::cout << "\nList of parameters:\n";
        for (std::size_t i = 0; i < param.size(); ++i) {
            std::cout << i << ") " << get_param_name(i) << std::endl;
        }
    }

    virtual void set_param(std::size_t n, float val) = 0;

    Shape& operator=(const Shape& s) {
        x = s.x;
        y = s.y;
        for (std::size_t i = 0; i < param.size(); ++i) {
            param.at(i) = s.param.at(i);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Shape& s) {
        s.print(os);
        return os;
    }

    virtual std::string get_param_name(std::size_t n) const = 0;
    virtual std::size_t get_number_of_params() {return param.size();}

protected:
    virtual void print(std::ostream& os) const = 0;

    std::vector<float> param;
    std::vector<std::string> param_name;

    int x, y;
    bool shown;
};


class Circle : public Shape {
public:
    Circle(float r):
        Shape(1),
        param_name({"radius"}),
        param({r}),
        shape(sf::CircleShape(r)) {};

    void display(sf::RenderWindow& w) override {
        shape.setRadius(param[0]);
        w.draw(shape);
    }

    void set_pos(int _x, int _y) override {
        x = _x;
        y = _y;
        shape.setPosition(x, y);
    }

    void set_param(std::size_t n, float val) override {
        param.at(n) = val;
    }

    std::string get_param_name(std::size_t n) const override {return param_name.at(n);}

protected:
    void print(std::ostream& os) const override {os << "Circle(r = " << param[0] << ")";}

    std::vector<float> param;
    std::vector<std::string> param_name;

    sf::CircleShape shape;
};


class Rect : public Shape {
public:
    Rect(float w, float h):
        Shape(3),
        param_name({"width", "height", "angle"}),
        param({w, h, 0}),
        shape(sf::RectangleShape({w, h}))
    {
        shape.setOutlineColor(sf::Color(0, 0, 0));
        shape.setOutlineThickness(3);
    };

    void display(sf::RenderWindow& w) override {
        shape.setSize({param[0], param[1]});
        shape.setRotation(param[2]);
        w.draw(shape);
    }

    void set_pos(int _x, int _y) override {
        x = _x;
        y = _y;
        shape.setPosition(x, y);
    }

    void set_param(std::size_t n, float val) override {
        param.at(n) = val;
    }

    std::string get_param_name(std::size_t n) const override {return param_name.at(n);}

protected:
    void print(std::ostream& os) const override {os << "Rect(r = " << param[0] << ")";}

    std::vector<float> param;
    std::vector<std::string> param_name;

    sf::RectangleShape shape;
};


class Window {
public:
    Window(): window(sf::RenderWindow{ { 800, 600 }, "Task5" }) {}
    void update() {
        window.clear(sf::Color(50, 50, 50));

        for (Shape* s: shapes) {
            if (s->isShown()) {s->display(window);}
        }

        window.display();
    }

    void close() {
        window.close();
    }

    void add_shape(Shape* s) {shapes.push_back(s);}
    void add_shape(Shape& s) {shapes.push_back(&s);}

    void set_shape_pos(std::size_t n, int x, int y) {
        (*shapes.at(n)).set_pos(x, y);
    }

    void move_shape(std::size_t n, int dx, int dy) {
        (*shapes.at(n)).move(dx, dy);
    }

    void delete_shape(std::size_t n) {
        delete shapes.at(n);
        shapes.erase(shapes.begin() + n);
    }

    void print_shapes() {
        std::cout << "\nList of shapes:\n";
        for (std::size_t i = 0; i < shapes.size() ; ++i) std::cout << "  " << i << ") " << *shapes.at(i) << std::endl;
    }

    void print_shape_params(std::size_t n) {
        shapes.at(n)->print_params();
    }

    void set_shape_param(std::size_t shape_n, std::size_t param_n, float val) {
        shapes.at(shape_n)->set_param(param_n, val);
    }

    void switch_shape_shown(std::size_t n) {
        if (shapes.at(n)->isShown()) shapes.at(n)->hide();
        else shapes.at(n)->show();
    }
private:
    std::vector<Shape*> shapes;
    sf::RenderWindow window;
};

#endif // SHAPE_INCLUDED
