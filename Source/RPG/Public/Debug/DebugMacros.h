#pragma once

#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true);
#define DRAW_SPHERE_FRAME(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, false, -1.f);
#define DRAW_LINE(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, StartLocation + EndLocation * 100.f, FColor::Red, true);
#define DRAW_LINE_FRAME(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, StartLocation + EndLocation * 100.f, FColor::Red, false, -1.f);
#define DEBUG_MESSAGE(x, y) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, y, FColor::Yellow, x);}
//FString::Printf(TEXT("Current GroundSpeed: %.2f"), GroundSpeed