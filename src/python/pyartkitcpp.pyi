
#*##################################################
#*################# Colors #########################
#*##################################################

class Color:

    red: int
    green: int
    blue: int

    def __init__(self, red: int, green: int, blue: int): ...


class ColorScheme:
    pass


class StaticColorSchemeType(ColorScheme):

    color: Color

    def __init__(self, color: Color): ...


class HorizontalGradientColorScheme(ColorScheme):

    left_color: Color
    right_color: Color
    left_bound: int
    right_bound: int

    def __init__(self, left_color: Color, right_color: Color, left_bound: int, right_bound: int): ...

    def set_left_bound(self, left_bound: int): ...

    def set_right_bound(self, right_bound: int): ...

    def set_right_color(self, right_color: Color): ...

    def set_left_color(self, left_color: Color): ...


class VerticalGradientColorScheme(ColorScheme):

    top_color: Color
    bottom_color: Color
    top_bound: int
    bottom_bound: int

    def __init__(self, top_color: Color, bottom_color: Color, top_bound: int, bottom_bound: int): ...

    def set_top_bound(self, top_bound: int): ...

    def set_bottom_bound(self, bottom_bound: int): ...

    def set_bottom_color(self, bottom_color: Color): ...

    def set_top_color(self, top_color: Color): ...


class RadialGradientColorScheme(ColorScheme):
    
    center_color: Color
    edge_color: Color
    center_x: int
    center_y: int
    radius: int

    def __init__(self, center_color: Color, edge_color: Color, center_x: int, center_y: int, radius: int): ...

    def set_center(self, center_x: int, center_y: int): ...

    def set_radius(self, radius: int): ...

    def set_edge_color(self, edge_color: Color): ...

    def set_center_color(self, center_color: Color): ...


#*##################################################
#*################# Shapes #########################
#*##################################################

class Shape:
    pass


class Circle(Shape):

    # x: int
    # y: int
    # radius: int

    def __init__(self, x: int, y: int, radius: int): ...

    def translate(self, dx: int, dy: int): ...


class Polygon(Shape):

    # points: list[tuple[int, int]]

    def __init__(self, points: list[tuple[int, int]]): ...

    def translate(self, dx: int, dy: int): ...


class Ellipse(Shape):

    # x: int
    # y: int
    # radius_x: int
    # radius_y: int

    def __init__(self, x: int, y: int, x_radius: int, y_radius: int): ...

    def translate(self, dx: int, dy: int): ...


class HalfCircle(Shape):

    # x: int
    # y: int
    # radius: int
    # normalVector: tuple[int, int]

    def __init__(self, x: int, y: int, radius: int, normalVector: tuple[int, int]): ...

    def translate(self, dx: int, dy: int): ...

#*##################################################
#*################# Canvas #########################
#*##################################################

class Canvas:

    width: int
    height: int

    def __init__(self, width: int, height: int, background_color: Color): ...

    def resize(self, new_width: int, new_height: int): ...

    def set_pixel(self, x: int, y: int, color: Color): ...

    def to_png(self, filename: str): ...

    def add_shape(self, shape: Shape, fill_color: (Color | ColorScheme), border_color: (Color | ColorScheme)): ...
