t = 1:1:20;
Turb = [1554.43, 1798.10, 1798.10, 1798.10, 1798.10, 1798.10, 1798.10, ...
     1798.10, 1798.10, 1798.10, 1798.10, 1798.10, 1798.10, 1798.10, 1798.10,...
      1798.10, 1798.10, 1798.10,  1798.10,  1798.10];
TargetTurb = [1798,1798,1798,1798,1798,1798,1798,1798,1798,1798,1798,...
    1798,1798,1798,1798,1798,1798,1798,1798,1798,];
Turb1 = 1797 * ones(1, 20);
Turb2 = 1799 * ones(1, 20);

Temp = [20.00, 23.25, 26, 28.5, 30.25, 32.25, 32.75, 32.50, 32.75, 32, 32.50,...
    32.5, 32.5, 32.5, 32.5, 32.5, 32.5, 32.5, 32.25, 32.5];
TargetTemp = [32.5,32.5,32.5,32.5,32.5,32.5,32.5,32.5,32.5,32.5,...
    32.5,32.5,32.5,32.5,32.5,32.5,32.5,32.5,32.5,32.5,];
Temp1 = 32 * ones(1,20);
Temp2 = 33 * ones(1,20);

TDS = [127, 127, 127, 127, 336, 587, 609, 632, 638, 640, 640, 640, 640, 640,...
    640, 643, 643, 643, 640, 640];
TargetTDS = [638,638,638,638,638,638,638,638,638,638,638,638,638,638,638,...
    638,638,638,638,638];
TDS1 = 618 * ones(1,20);
TDS2 = 658 * ones(1,20);

subplot(3,1,1)
plot(t,Turb,'Marker','*')
ylim([1790,1805])
title('Turbidity Sensor Settling Time')
xlabel('Time(s)')
ylabel('Turbidity(NTU)')
hold on 
plot(t,TargetTurb,'LineWidth', 2)
hold on
plot(t, Turb1, 'LineStyle','--', 'color','r')
plot(t, Turb2, 'LineStyle','--', 'color','r')
legend('Measured Value','Target Value','Threshold','Location','SouthEast')


subplot(3,1,2)
plot(t, Temp,'Marker','*')
title('Temperature Sensor Settling Time')
xlabel('Time(s)')
ylabel('Temperature(Degree in C)')
hold on 
plot(t,TargetTemp,'LineWidth', 2)
hold on
plot(t, Temp1, 'LineStyle','--', 'color','r')
plot(t, Temp2, 'LineStyle','--', 'color','r')
legend('Measured Value','Target Value','Threshold','Location','SouthEast')

subplot(3,1,3)
plot(t, TDS,'Marker','*')
hold on
plot(t,TargetTDS,'LineWidth', 2)
title('TDS Sensor Settling Time')
xlabel('Time(s)')
ylabel('Conductivity(ppm)')
hold on
plot(t, TDS1, 'LineStyle','--', 'color','r')
plot(t, TDS2, 'LineStyle','--', 'color','r')
legend('Measured Value','Target Value','Threshold','Location','SouthEast')