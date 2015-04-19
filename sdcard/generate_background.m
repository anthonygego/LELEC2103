function generate_background

img = zeros(480,800,3,'uint8');

for i=1:480
    value =  16711680 + bitshift(floor(i*255/480),8);
    for j=1:800
        for k=1:3
            img(i,j,k) = bitand(bitshift(value, -(3-k)*8), 255);
        end
    end
end

imwrite(img, 'img/background.png');
end

