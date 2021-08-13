%%Hard-iron offset: X = -56.50, Y = 10.24, Z = -1.380
%%Gyroscope zero offset: X = -0.1296, Y = 0.1720, Z = -0.02773

A = dlmread('test.txt', ','); %replace test.txt with the name of the file to analyze; reads in text file data
B = zeros(size(A,1),14); %create a matrix (of zeros) with the same dimensions as A
B(1,:) = A(1,:); %assign the matrix B to be a copy of matrix A

%The following commented block removes any duplicate sensor readings that
%may appear in a text file. Not needed for now.
%counter = 2; %prevents code from erroring out when trying to subtract the first line from itself
%for i = 2:size(A,1)
    %if A(i,1) ~= A(i-1,1)
        %B(counter,:) = A(i,:);
        %counter = counter + 1;
    %end
%end
%B = B(1:(counter - 1),:);

B(:,3) = B(:,3) - 9.806; %Correct for acceleration due to gravity in the y-direction

B(:,4) = B(:,4) + 0.1296; %Correct for corresponding gyroscope zero offsets
B(:,5) = B(:,5) - 0.1720;
B(:,6) = B(:,6) + 0.02773;

B(:,7) = B(:,7) + 56.50; %Correct for corresponding magnetometer hard-iron offsets
B(:,8) = B(:,8) - 10.24;
B(:,9) = B(:,9) + 1.380;

C = B;

%The following seven variables will be used by another script titled "MadgwickScript"
Accelerometer = C(:,1:3);
Gyroscope = C(:,4:6);
Magnetometer = C(:,7:9);
FSR = C(:,10:11); %force-sensitive resistor
HES = C(:,12); %hall effect sensor
time = C(:,13);
button = C(:,14);

%%
v_ix = 0; %initial velocity for given coordinate axis
v_iy = 0;
v_iz = 0;
x_i = 0; %initial position for given coordinate axis
y_i = 0; 
z_i = 0; 

calibrate_ax = C(1,1); %Used to correct all data points with a starting acceleration of zero on a given axis
calibrate_ay = C(1,2);
calibrate_az = C(1,3);

C(1,1) = x_i; C(1,2) = y_i; C(1,3) = z_i;

x_pos = [0]; %vectors to hold the calculated position on a given axis at each collected time point
y_pos = [0];
z_pos = [0];

for index1 = 1:size(C,1)
        if (index1 == 1)
            dt = A(index1 + 1,13) - A(index1,13); %prevents an error when no prior time value is present
        else
            dt = A(index1,13) - A(index1 - 1,13);
        end
        C(index1,13) = dt;
        a_x = C(index1, 1) - calibrate_ax;
        v_fx = v_ix + a_x*dt; %kinematic formula for updated velocity
        x_f = x_i + v_fx*dt + 0.5*a_x*(dt^2); %kinematic formula for updated position
        C(index1,1)= x_f;
        v_ix = v_fx;
        x_i = x_f;
        
        a_y = C(index1, 2) - calibrate_ay;
        a_y = a_y;
        v_fy = v_iy + a_y*dt; %kinematic formula for updated velocity
        y_f = y_i + v_fy*dt + 0.5*a_y*(dt^2); %kinematic formula for updated position
        C(index1,2)= y_f;
        v_iy = v_fy;
        y_i = y_f;
        
        a_z = C(index1, 3) - calibrate_az;
        v_fz = v_iz + a_z*dt; %kinematic formula for updated velocity
        z_f = z_i + v_fz*dt + 0.5*a_z*(dt^2); %kinematic formula for updated position
        C(index1,3)= z_f;
        v_iz = v_fz;
        z_i = z_f;
        
        x_pos = [x_pos x_f];
        y_pos = [y_pos, y_f];
        z_pos = [z_pos, z_f];
end

plot3(x_pos, y_pos, z_pos) %generate an x,y,z plot of the IMU's positional data
xlabel('x-axis')
ylabel('y-axis')
zlabel('z-axis')

%make the text file matrix and its component data variables/columns
%accessible by the script "MadgwickScript.m"
save test.mat Accelerometer Gyroscope Magnetometer FSR HES time button %change test to the desired file name for analysis
