ROUTINE MDX2JSON.MDX2JSON [Type=INC]
#include %occErrors
#include %ZEN.Utils
#include %DeepSee

#define get(%name) $get(%request.Data(%name,1))
#define WebContext $d(%request)'=0
#define Debug (($$$WebContext) && ($d(%request.Data("Debug"))))
#define R(%property) %request.Content.##Expression(%property)
#define Public ((%request.GetCgiEnv("SERVER_PORT") = 80) || (%request.GetCgiEnv("SERVER_PORT") = 443))
#define Private '$$$Public
#define Global ^MDX2JSON
#define Settings "Settings"
#define Features "Features"
#define DefaultUser "DeepSeeWeb"
#define DefaultSettingsRole "MDX2JSONSettings"

#; For work with dynamic objects
#if (($$$comClassDefined("%Library.AbstractObject"))&&($get($$$Global($$$Features))["newjson"))
	#define NewDynObj ##class(%Object).%New()
	#define NewDynDTList ##class(%Array).%New()
	#;define NewDynDTArray $$$NewDynDTList
	#define NewDynObjList $$$NewDynDTList
	#;define NewDynObjArray $$$NewDynDTList
	#define Insert(%obj,%element) do %obj.$push(%element)
	#define DynObjToJSON(%obj) w %obj.$toJSON()
	#define ListToJSON(%obj) $$$DynObjToJSON(%obj)
	#define ListSize(%obj) %obj.$size()
	#define ListGet(%obj,%i) %obj.$get(%i-1)
#else
	#define NewDynObj ##class(%ZEN.proxyObject).%New()
	#define NewDynDTList ##class(%ListOfDataTypes).%New()
	#;define NewDynDTArray ##class(%ArrayOfDataTypes).%New()
	#define NewDynObjList ##class(%ListOfObjects).%New()
	#;define NewDynObjArray ##class(%ArrayOfObjects).%New()
	#define Insert(%obj,%element) do %obj.Insert(%element)
	#define DynObjToJSON(%obj) do %obj.%ToJSON()
	#define ListToJSON(%obj) do ##class(%ZEN.Auxiliary.jsonProvider).%ObjectToJSON(%obj)
	#define ListSize(%obj) %obj.Count()
	#define ListGet(%obj,%i) %obj.GetAt(%i)
#endif
#define IsNewJSON ##Expression($$$comClassDefined("%Library.AbstractObject"))
#define JSONEnabled ($get($$$Global($$$Features))["newjson")