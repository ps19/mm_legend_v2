#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
}

#include "mock_templates.hpp"
#include "mocks/map_validate_mocks.hpp"

#define WALL_THRESHOLD          20.0f
#define CORNER_THRESHOLD        30.0f
#define DELTA                           0.01f

TEST_GROUP(map_update_present)
{
    void setup()
    {
    }

    void teardown()
    {
        mapValidateWallLeftMockSet(nullptr);
        mapValidateWallRightMockSet(nullptr);
        mapValidateWallTopMockSet(nullptr);
        mapValidateWallBottomMockSet(nullptr);
    }
};

TEST(map_update_present, LeftWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallLeftMock.getCount());
    CHECK_EQUAL(17, mapValidateWallLeftMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallLeftMock.getArg2());
}

TEST(map_update_present, LeftWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallLeftMock.getCount());
    CHECK_EQUAL(18, mapValidateWallLeftMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallLeftMock.getArg2());
}

TEST(map_update_present, LeftWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, LeftWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMinimalTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMinimalTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallLeftMock;

    mapValidateWallLeftMockSet(&mapValidateWallLeftMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallLeftMock.getCount());
}

TEST(map_update_present, BottomWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallBottomMock.getCount());
    CHECK_EQUAL(17, mapValidateWallBottomMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallBottomMock.getArg2());
}

TEST(map_update_present, BottomWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallBottomMock.getCount());
    CHECK_EQUAL(18, mapValidateWallBottomMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallBottomMock.getArg2());
}

TEST(map_update_present, BottomWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, BottomWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMinimalTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMinimalTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallBottomMock;

    mapValidateWallBottomMockSet(&mapValidateWallBottomMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallBottomMock.getCount());
}

TEST(map_update_present, RightWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallRightMock.getCount());
    CHECK_EQUAL(17, mapValidateWallRightMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallRightMock.getArg2());
}

TEST(map_update_present, RightWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 3 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallRightMock.getCount());
    CHECK_EQUAL(18, mapValidateWallRightMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallRightMock.getArg2());
}

TEST(map_update_present, RightWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, RightWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, RightWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, RightWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, RightWallDetectedMinimalTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, RightWallDetectedMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, RightWallDetectedMinimalTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, RightWallDetectedMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallRightMock;

    mapValidateWallRightMockSet(&mapValidateWallRightMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallRightMock.getCount());
}

TEST(map_update_present, TopWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallTopMock.getCount());
    CHECK_EQUAL(17, mapValidateWallTopMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallTopMock.getArg2());
}

TEST(map_update_present, TopWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallTopMock.getCount());
    CHECK_EQUAL(18, mapValidateWallTopMock.getArg1());
    CHECK_EQUAL(MAP_WALL_PRESENT, mapValidateWallTopMock.getArg2());
}

TEST(map_update_present, TopWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallTopMock.getCount());
}

TEST(map_update_present, TopWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallTopMock.getCount());
}

TEST(map_update_present, TopWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallTopMock.getCount());
}

TEST(map_update_present, TopWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallTopMock.getCount());
}

TEST(map_update_present, TopWallDetectedMinimalTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallTopMock.getCount());
}

TEST(map_update_present, TopWallDetectedMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallTopMock.getCount());
}

TEST(map_update_present, TopWallDetectedMinimalTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapValidateWallTopMock.getCount());
}

TEST(map_update_present, TopWallDetectedMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapValidateWallMock mapValidateWallTopMock;

    mapValidateWallTopMockSet(&mapValidateWallTopMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapValidateWallTopMock.getCount());
}
