// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RequestType.generated.h"

UENUM(BlueprintType)
enum class ERequestType : uint8
{
	Login			UMETA(DisplayName = "Login"),
	Register		UMETA(DisplayName = "Register")
};
