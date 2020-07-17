#ifndef ___Tornado__Constants__H___
#define ___Tornado__Constants__H___

/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Constantes globales del motor                              *
 * Archivo Fuente: Constants.h                                        *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#if !defined(FILE_CONFIG)
//! Nombre del archivo de configuracion
#define FILE_CONFIG		L"config.ini"
#endif

#ifndef FOLDER_CACHE
//! Nombre del directorio cache
#define FOLDER_CACHE	L"cache"
#endif

#ifndef FOLDER_SAVE
//! Nombre del directorio cache
#define FOLDER_SAVE		L"save"
#endif

//! Constante Plataforma Win32
#define __TORNADO_PLATFORM_WIN32 1
//! Constante Plataforma Linux
#define __TORNADO_PLATFORM_LINUX 2
//! Constante Plataforma Apple
#define __TORNADO_PLATFORM_APPLE 3

//! Constante Arquitectura 32-bits
#define __TORNADO_ARCHITECTURE_32 1
//! Constante Arquitectura 64-bits
#define __TORNADO_ARCHITECTURE_64 2

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined(WIN32)
#//! Constante Tipo Plataforma
#define __TORNADO_PLATFORM __TORNADO_PLATFORM_WIN32
#define __TORNADO_DLL_EXPORT __declspec(dllexport)
#define __TORNADO_DLL_IMPORT __declspec(dllexport)
#elif defined( __APPLE_CC__)
#define __TORNADO_PLATFORM __TORNADO_PLATFORM_APPLE
#define __TORNADO_DLL_EXPORT
#define __TORNADO_DLL_IMPORT
#else
#define __TORNADO_PLATFORM __TORNADO_PLATFORM_LINUX
#define __TORNADO_DLL_EXPORT
#define __TORNADO_DLL_IMPORT
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
//! Constante Tipo Arquitectura
#define __TORNADO_ARCH_TYPE __TORNADO_ARCHITECTURE_64
#else
#define __TORNADO_ARCH_TYPE __TORNADO_ARCHITECTURE_32
#endif
#endif

