#pragma once

namespace gps
{
    struct LatLon 
    {
        LatLon():lat(0.0), lon(0.0){};
        LatLon(double la, double lo):lat(la), lon(lo){}; 
        double lat = 0.0;
        double lon = 0.0;
    };
} 
