function y = convertToQ31(x)
    m = 0;
    n = 31;
    y = int32(round(x * 2^n));
end
