%Matthew Capuano- Biploar AF BCD -> 7Seg

clear all



inputs = [-1 -1	-1;         %define input values

-1	-1	1;

-1	1	-1;

-1	1	1;

1	-1	-1;

1	-1	1;

1	1	-1;

1	1	1];





outputs = [1	1 1	1 1	1 -1; %define output values

-1 1 1 -1 -1 -1 -1;

1 1 -1 1 1 -1 1;

1 1	1 1 -1 -1 1;

-1 1 1 -1 -1 1 1;

1 -1 1 1 -1	1 1;

1 -1 1 1 1 1 1;

1 1	1 -1 -1	-1 -1];





weights = zeros(7,3);



for i = 1:1:8               %calculate W

    a = inputs(i,:);

    b = outputs (i,:)';

    c = a.*b;

    weights = weights + c;

end



in_weights = weights';

                        %run inputs through weights, calculator Error

outputrun = zeros(8,7);



for i = 1:1:8

    d = inputs(i,:);

    e = d * in_weights;

    outputrun(i,:) = e;

end



for i = 1:1:8                           %run through bipolar AF

    for j = 1:1:7

        if (outputrun(i,j) > 0)

            outputrun(i,j) = 1;

        else

            outputrun(i,j) = -1;

        end

    end

end



error = 0;                          %calculate number of incorrect output vectors



for i = 1:1:8

    if outputrun(i,:) == outputs(i,:)

        error = error;

    else

        error = error + 1;

    end



end



cellerror = 0;                  %calculate number of incorrect output cells

for i = 1:1:8

    for j = 1:1:7

        if outputrun(i,j) == outputs(i,j)

            cellerror = cellerror;

        else

            cellerror = cellerror + 1;
            %training fn 3/12
            pp = inputs(i,:);
            zz = outputs(i,:)';
            cc = pp.*b;
            for p = 1:1:3
            weights(p,j) =  weights(p,j) + cc(p,j);
            end
            %end training fn 3/12
        end

    end

end



                             

                             %output values

 inputs

 in_weights

 outputs

 outputrun

 error

 cellerror