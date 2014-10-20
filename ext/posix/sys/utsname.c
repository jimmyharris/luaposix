/*
 * POSIX library for Lua 5.1/5.2.
 * (c) Gary V. Vaughan <gary@vaughan.pe>, 2013-2014
 * (c) Reuben Thomas <rrt@sc3d.org> 2010-2013
 * (c) Natanael Copa <natanael.copa@gmail.com> 2008-2010
 * Clean up and bug fixes by Leo Razoumov <slonik.az@gmail.com> 2006-10-11
 * Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br> 07 Apr 2006 23:17:49
 * Based on original by Claudio Terra for Lua 3.x.
 * With contributions by Roberto Ierusalimschy.
 * With documentation from Steve Donovan 2012
 */
/***
 Get System Identification.

@module posix.sys.utsname
*/

#include <config.h>

#include <sys/utsname.h>

#include "_helpers.c"


/***
System identification record.
@table utsname
@string machine hardware platform name
@string nodename network node name
@string release operating system release level
@string sysname operating system name
@string version operating system version
*/

static int
pushutsname(lua_State *L, struct utsname *u)
{
	if (!u)
	{
		lua_pushnil(L);
		return 1;
	}

	lua_createtable(L, 0, 5);
	if (u->machine)
	{
		lua_pushstring(L, u->machine);
		lua_setfield(L, -2, "machine");
	}
	if (u->nodename)
	{
		lua_pushstring(L, u->nodename);
		lua_setfield(L, -2, "nodename");
	}
	if (u->release)
	{
		lua_pushstring(L, u->release);
		lua_setfield(L, -2, "release");
	}
	if (u->sysname)
	{
		lua_pushstring(L, u->sysname);
		lua_setfield(L, -2, "sysname");
	}
	if (u->version)
	{
		lua_pushstring(L, u->version);
		lua_setfield(L, -2, "version");
	}
	return 1;
}


/***
Return information about this machine.
@function uname
@treturn[1] utsname system information
@return[2] nil
@treturn[2] string error message
@see uname(2)
*/
static int
Puname(lua_State *L)
{
	struct utsname u;
	checknargs(L, 0);
	if (uname(&u)==-1)
		return pusherror(L, "uname");
	return pushutsname(L, &u);
}


static const luaL_Reg posix_sys_utsname_fns[] =
{
	LPOSIX_FUNC( Puname		),
	{NULL, NULL}
};


LUALIB_API int
luaopen_posix_sys_utsname(lua_State *L)
{
	luaL_register(L, "posix.sys.utsname", posix_sys_utsname_fns);
	lua_pushliteral(L, "posix.sys.utsname for " LUA_VERSION " / " PACKAGE_STRING);
	lua_setfield(L, -2, "version");

	return 1;
}
