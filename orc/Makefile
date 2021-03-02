include $(TOPDIR)/rules.mk

PKG_NAME:=orc
PKG_VERSION:=0.1.0
PKG_RELEASE:=1

PKG_MAINTAINER:=Malte Granderath <malte.granderath@gmail.com>
PKG_LICENSE:=BSD-3-Clause
TARGET_CFLAGS += -ggdb3

SOURCE_DIR:=/restconf

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk
TARGET_CFLAGS += -g3

define Build/Compile
    $(MAKE) -C $(PKG_BUILD_DIR)/ \
    CC="$(TARGET_CC)" \
    CFLAGS="$(TARGET_CFLAGS)"
endef

define Package/orc
	SECTION:=utils
	DEPENDS:=+libuci +libjson-c +libubox +uhttpd
	CATEGORY:=Utilities
	TITLE:=RESTCONF for OpenWrt
	URL:=https://github.com/mgranderath/orc
endef

define Package/orc/description
	RESTCONF for OpenWrt
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -a $(SOURCE_DIR)/* $(PKG_BUILD_DIR)/
endef

define Package/orc/install
	$(INSTALL_DIR) $(1)/www/cgi-bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/restconf $(1)/www/cgi-bin/
endef

$(eval $(call BuildPackage,orc))