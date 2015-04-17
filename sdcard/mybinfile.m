function mybinfile

[cdata , ~, alpha] = imread('glossy-ball.png');

fileID = fopen('textures.bin', 'w');

for i= 1:20
    for j=1:20
        fwrite(fileID, 255, 'uint8');
        for k=1:3
            fwrite(fileID, cdata(i,j,k), 'uint8');
        end
    end
end

for i= 1:20
    for j=1:20
        fwrite(fileID, 255-alpha(i,j), 'uint8');
    end
end

fclose(fileID);


end

