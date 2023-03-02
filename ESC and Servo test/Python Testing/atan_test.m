clc
clear all
close all

xStickValue = 0;
yStickValue = 0;
angleInRads = 0.0;
angleInDeg = 0.0;
roundedAngleInDeg = 0;

PI = pi;

% Radius of the circle
radius = 10;

% for x = -10:10
%     for y = -10:10
%         if x^2 + y^2 <= 10^2
%             polar_coords = [x, y]
%             angleToDegs(x,y)
%         end
%     end
% end


r = 10;
[x,y] = meshgrid(-r:r,-r:r);
mask = x.^2 + y.^2 <= r^2;
theta = round(atan2(y(mask),x(mask)) * (180/pi));
rho = round(sqrt(x(mask).^2 + y(mask).^2));
polar_coords = [theta(:)];

cartesian_coords = [x(mask(:)), y(mask(:))];

coords_table = [cartesian_coords,polar_coords];

disp(coords_table)