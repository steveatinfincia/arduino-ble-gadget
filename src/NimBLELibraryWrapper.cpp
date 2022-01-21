#include "NimBLELibraryWrapper.h"
#include "NimBLEDevice.h"

uint NimBLELibraryWrapper::_numberOfInstances = 0;

struct WrapperPrivateData {
    NimBLEAdvertising* _pNimBLEAdvertising;
};

WrapperPrivateData* NimBLELibraryWrapper::_data = nullptr;

NimBLELibraryWrapper::NimBLELibraryWrapper() {
    if(NimBLELibraryWrapper::_numberOfInstances++ == 0) {
        NimBLELibraryWrapper::_data = new WrapperPrivateData();
        init();
    }
}

NimBLELibraryWrapper::~NimBLELibraryWrapper() {
    if(NimBLELibraryWrapper::_numberOfInstances-- == 1) {
        NimBLEDevice::deinit();
        delete NimBLELibraryWrapper::_data;
    }
}

void NimBLELibraryWrapper::init() {
    NimBLEDevice::init(GADGET_NAME);

    NimBLELibraryWrapper::_data->_pNimBLEAdvertising = NimBLEDevice::getAdvertising();
    // Helps with iPhone connection issues (copy/paste)
    NimBLELibraryWrapper::_data->_pNimBLEAdvertising->setMinPreferred(0x06);
    NimBLELibraryWrapper::_data->_pNimBLEAdvertising->setMaxPreferred(0x12);
}

void NimBLELibraryWrapper::setAdvertisingData(const std::string& data) {
    NimBLEAdvertisementData advert;
    advert.setName(GADGET_NAME);
    advert.setManufacturerData(data);
    NimBLELibraryWrapper::_data->_pNimBLEAdvertising->setAdvertisementData(advert);
}

void NimBLELibraryWrapper::startAdvertising() {
    NimBLELibraryWrapper::_data->_pNimBLEAdvertising->start();
}

void NimBLELibraryWrapper::stopAdvertising() {
    NimBLELibraryWrapper::_data->_pNimBLEAdvertising->stop();
}
std::string NimBLELibraryWrapper::getDeviceAddress() {
    return NimBLEDevice::getAddress().toString();
}