function [roundedAngleInDeg] = angleToDegs(xStickValue,yStickValue)

if ((xStickValue == 0) && (yStickValue == 0))
    roundedAngleInDeg = 0;
elseif ((xStickValue== 0) && (yStickValue > 0))
    roundedAngleInDeg = 0;
elseif ((xStickValue == 0) && (yStickValue < 0))
    roundedAngleInDeg = 180;
elseif ((xStickValue > 0) && (yStickValue == 0))
    roundedAngleInDeg = 90;
elseif ((xStickValue < 0) && (yStickValue == 0))
    roundedAngleInDeg = 270;
elseif (xStickValue > 0)
    angleInDeg = atan2(xStickValue, yStickValue) * (180/pi);
    roundedAngleInDeg = round(angleInDeg);
elseif (xStickValue < 0)
    angleInDeg = 2 * pi + atan2(xStickValue, yStickValue) * (180/pi);
    roundedAngleInDeg = round(angleInDeg);
end

