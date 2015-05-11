function preview_boni_mali()

img = uint8(zeros(320, 240, 3));

for i=1:109
    for j=1:119
        img(i, j, :) = [0;0;255];
    end
end

for i=1:109
    for j=121:240
        img(i, j, :) = [255;0;0];
    end
end

for i=111:219
    for j=1:119
        img(i, j, :) = [128;0;64];
    end
end

for i=111:219
    for j=121:240
        img(i, j, :) = [0;255;0];
    end
end

for i=221:255
    for j=1:240
        img(i, j, :) = [255;255;0];
    end
end

for i=257:320
    for j=1:119
        img(i, j, :) = [0;222;128];
    end
end

for i=257:320
    for j=121:240
        img(i, j, :) = [0;222;128];
    end
end


test = figure();

imshow(img,'Border','tight');

text(20,50,'Life +1','Color','w','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');
text(150,50,'Life -1','Color','w','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');
text(20,150,'Larger/','Color','w','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');
text(20,175,'Smaller','Color','w','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');
text(140,165,'Brick +1','Color','w','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');
text(45,237,'Slower / Faster','Color','k','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');
text(55,287,'-','Color','k','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');
text(175,287,'+','Color','k','FontWeight','Bold','FontSize',14, 'FontName', 'Tahoma');

tim = getframe(test);
img = tim.cdata;

imwrite(img, 'boni_mali.png');
end

