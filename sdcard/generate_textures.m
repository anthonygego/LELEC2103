function generate_textures

fileID = fopen('textures.bin', 'w');

[cdata , ~, alpha] = imread('img/ball.png');

for i= 1:20
    for j=1:20
        for k=3:-1:1
            fwrite(fileID, cdata(i,j,k), 'uint8');
        end
        fwrite(fileID, 0, 'uint8');
    end
end

for i= 1:20
    for j=1:20
        fwrite(fileID, 255-alpha(i,j), 'uint8');
    end
end

for l=[200 100]
    [cdata , ~, ~] = imread(sprintf('img/paddle%d.jpg', l));

    for i= 1:20
        for j=1:l
            for k=3:-1:1
                fwrite(fileID, cdata(i,j,k), 'uint8');
            end
            fwrite(fileID, 0, 'uint8');
        end
    end

    for i= 1:20
        for j=1:l
            fwrite(fileID, 0, 'uint8');
        end
    end
end

for l=1:4

    [cdata , ~, ~] = imread(sprintf('img/brick%d.jpg', l));

    for i= 1:20
        for j=1:50
            for k=3:-1:1
                fwrite(fileID, cdata(i,j,k), 'uint8');
            end
            fwrite(fileID, 0, 'uint8');
        end
    end

end

fclose(fileID);


end

