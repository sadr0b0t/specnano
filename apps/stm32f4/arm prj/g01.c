#include"inc/g01.h"
#include"inc/gcode.h"
#include"inc/g.h"
#include <syniopsis.h>

double MyAbs(double Val){
  if(Val<0){
    return Val*(-1);
  }else{
    return Val;
  }
}

void g01_enter_point (double x1, double y1, double z1, double f) {
  double NewX=0, NewY=0, NewZ=0;
  double dX, dY, dZ;
  int   Counter;
  
  MovP.X_offset = x1 - g_x0;
  MovP.Y_offset = y1 - g_y0;
  MovP.Z_offset = z1 - g_z0;

  // Число точек - максимальное значение одной из координат
  MovP.NumOfPositions = (int)(MyAbs(MovP.X_offset));
  if(MovP.NumOfPositions<MyAbs(MovP.Y_offset))MovP.NumOfPositions = (int)(MyAbs(MovP.Y_offset));
  if(MovP.NumOfPositions<MyAbs(MovP.Z_offset))MovP.NumOfPositions = (int)(MyAbs(MovP.Z_offset));
        
  // Теперь в x_offset, y_offset и z_offset находятся относительные значения
  // координаты новой точки, в MovP.NumOfPositions - количество точек.
  // Теперь необходимо провести анализ и построить траекторию движения.

  dX = MovP.X_offset/(double)(MovP.NumOfPositions);
  dY = MovP.Y_offset/(double)(MovP.NumOfPositions);
  dZ = MovP.Z_offset/(double)(MovP.NumOfPositions);

  for(Counter=0;Counter<MovP.NumOfPositions;Counter++){
    NewX += dX;
    NewY += dY;
    NewZ += dZ;
    
    // Заполняем массив точек. Собственно, линейная итерполяция . )
    // Сперва X
    if((MyAbs(NewX)+0.5)<1){
      MovP.NewPointOffsetX[Counter]=0;
    }else{
      MovP.NewPointOffsetX[Counter] = (char)(NewX);
      NewX -= MovP.NewPointOffsetX[Counter];
    }
    // потом Y
    if((MyAbs(NewY)+0.5)<1){
      MovP.NewPointOffsetY[Counter]=0;
    }else{
      MovP.NewPointOffsetY[Counter] = (char)(NewY);
      NewY -= MovP.NewPointOffsetY[Counter];
    }
    // и наконец Z
    if((MyAbs(NewZ)+0.5)<1){
      MovP.NewPointOffsetZ[Counter]=0;
    }else{
      MovP.NewPointOffsetZ[Counter] = (char)(NewZ);
      NewZ -= MovP.NewPointOffsetZ[Counter];
    }
  }

  Track();
  
	g_x0 = x1;
	g_y0 = y1;
	g_z0 = z1;	
        
        //Error_Status = 0;
        
	/*handle result*/
	if (handler_gcommand_result)
		handler_gcommand_result (g_x0, g_y0, g_z0, f);
}