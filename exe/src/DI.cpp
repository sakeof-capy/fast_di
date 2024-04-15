#include "C:\Users\admin\Desktop\diploma_work\Project\exe\include\exe\Application.hppdi"
#include "C:\Users\admin\Desktop\diploma_work\Project\exe\include\exe\Controllers\Controllers.hppdi"
#include "C:\Users\admin\Desktop\diploma_work\Project\exe\include\exe\Database\Database.hppdi"
#include "C:\Users\admin\Desktop\diploma_work\Project\exe\include\exe\Logger\Logger.hppdi"
#include "C:\Users\admin\Desktop\diploma_work\Project\exe\include\exe\Models\Models.hppdi"

void subscribe_all_dependencies()
{
	DI::subscribe_Application_();
	DI::subscribe_TaskController_();
	DI::subscribe_UserController_();
	DI::subscribe_PostgreSQLDatabase_();
	DI::subscribe_FileLogger_();
	DI::subscribe_TaskModel_();
	DI::subscribe_UserModel_();
}
