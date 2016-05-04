function y = convertToQ15(x)
    m = 0;
    n = 15;
    y = int16(round(x * 2^n));
end
