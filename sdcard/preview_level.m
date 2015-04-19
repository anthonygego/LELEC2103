function preview_level(level, paddle_size, ball_x, ball_y)

img = imread('img/background.png');

%% Paddle

paddle = imread(sprintf('img/paddle%d.jpg', intersect(paddle_size, [100 200])));

for i=1:20
    for j=1:paddle_size
        img(440+i,400-(paddle_size/2)+j,:) = paddle(i,j,:);
    end
end

%% Bricks

fileID = fopen(sprintf('level%02d.txt', level),'r');

formatSpec = '%c ';
sizeb = [14 12];
bricks = fscanf(fileID,formatSpec,sizeb);
fclose(fileID);

for l=1:12
    for m=1:14
			bvalue = bricks(m,l)- '0';
            if (bvalue > 0 && bvalue < 5)
                brick = imread(sprintf('img/brick%d.jpg', bvalue));

                for i=1:20
                    for j=1:50
                        img(45+(m-2)*20+m+i,45+l*50+l+j,:) = brick(i,j,:);
                    end
                end
            end
    end
end


%% Ball

[ballimg, ~, ballalpha] = imread('img/ball.png');

for i=1:20
    for j=1:20
        alpha = int32(ballalpha(i,j));
        v1 = int32(img(ball_y+i,ball_x+j,:))*(255-alpha);
        v2 = int32(ballimg(i,j,:))*alpha;
        img(ball_y+i,ball_x+j,:) = (v1+v2)/255;
    end
end

%% Walls

for i=1:8000
    value = ones(1,3,'uint8');
    if(mod(i,3)==0)
        value = value*42;
    else
        value = value*74;
    end
    
    if(i<=4400)   
        img(ceil(i/10),mod(i,10)+1, :) = value;
        img(ceil(i/10),790+mod(i,10)+1, :) = value;
    end
    img(mod(i,10)+1, ceil(i/10), :) = value;
end

imwrite(img, sprintf('preview/level%02d.png', level));
imwrite(imresize(img, 0.25), sprintf('preview_thumb/level%02d.jpg', level));
end

