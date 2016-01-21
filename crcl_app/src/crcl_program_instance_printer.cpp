#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tf/transform_datatypes.h>
#include <crcl_cpp/CRCLProgramInstanceClasses.hh>
#include "crcl_app/crcl_program_instance_handler.h"

static int handleMoveToType(MoveToType *cmd)
{
  double xi, xj, xk;
  double zi, zj, zk;
  double r, p, y;

  xi = cmd->EndPosition->XAxis->I->val;
  xj = cmd->EndPosition->XAxis->J->val;
  xk = cmd->EndPosition->XAxis->K->val;
  tf::Vector3 xaxis(xi, xj, xk);
  zi = cmd->EndPosition->ZAxis->I->val;
  zj = cmd->EndPosition->ZAxis->J->val;
  zk = cmd->EndPosition->ZAxis->K->val;
  tf::Vector3 zaxis(zi, zj, zk);
  tf::Vector3 yaxis = zaxis.cross(xaxis);
  tf::Matrix3x3 m(xi, yaxis.getX(), zi,
		  xj, yaxis.getY(), zj,
		  xk, yaxis.getZ(), zk);
  m.getRPY(r, p, y);

  printf("MoveToType(%d) %f %f %f / %f %f %f\n",
	 cmd->CommandID->val,
	 cmd->EndPosition->Point->X->val,
	 cmd->EndPosition->Point->Y->val,
	 cmd->EndPosition->Point->Z->val,
	 r, p, y
    );

  return 0;
}

static int handleSetEndEffectorType(SetEndEffectorType *cmd)
{
  printf("SetEndEffectorType(%d) %f\n",
	 cmd->CommandID->val,
	 cmd->Setting->val
    );
}

static int handleSetLengthUnitsType(SetLengthUnitsType *cmd)
{
  // can be 'meter', 'millimeter', or 'inch'
  printf("SetLengthUnitsType(%d) %s\n",
	 cmd->CommandID->val,
	 cmd->UnitName->val.c_str()
    );
}

static int handleSetAngleUnitsType(SetAngleUnitsType *cmd)
{
  // can be 'radian', or 'degree'
  printf("SetAngleUnitsType(%d) %s\n",
	 cmd->CommandID->val,
	 cmd->UnitName->val.c_str()
    );
}

static int handleSetTransSpeedType(SetTransSpeedType *cmd)
{
  TransSpeedAbsoluteType *a;
  TransSpeedRelativeType *r;

  printf("SetTransSpeedType(%d) ",
	 cmd->CommandID->val
    );

  if (NULL != (a = dynamic_cast<TransSpeedAbsoluteType *>(cmd->TransSpeed))) {
    printf("absolute %f\n", a->Setting->val);
  } else if (NULL != (r = dynamic_cast<TransSpeedRelativeType *>(cmd->TransSpeed))) {
    printf("relative %f\n", r->Fraction->val);
  } else {
    printf("unknown\n");
  }
}

int main(int argc, char * argv[])
{
  FILE * inFile;

  if (argc != 2) {
      fprintf(stderr, "Usage: %s <data file name>\n", argv[0]);
      return 1;
  }
  inFile = fopen(argv[1], "r");
  if (inFile == 0) {
    fprintf(stderr, "unable to open file %s for reading\n", argv[1]);
    return 1;
  }

  crcl_program_instance_handler_init(inFile);

  fclose(inFile);

  crcl_program_instance_handler_register(MoveToType, handleMoveToType);
  crcl_program_instance_handler_register(SetEndEffectorType, handleSetEndEffectorType);
  crcl_program_instance_handler_register(SetLengthUnitsType, handleSetLengthUnitsType);
  crcl_program_instance_handler_register(SetAngleUnitsType, handleSetAngleUnitsType);
  crcl_program_instance_handler_register(SetTransSpeedType, handleSetTransSpeedType);

  crcl_program_instance_handler_run();

  crcl_program_instance_handler_exit();

  return 0;
}
