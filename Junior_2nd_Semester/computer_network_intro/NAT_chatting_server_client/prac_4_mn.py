#!/usr/bin/python


import os

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.nodelib import NAT
from mininet.log import setLogLevel, info
from mininet.cli import CLI
from mininet.util import irange
from mininet.util import pmonitor
from mininet.link import TCLink
from mininet.clean import Cleanup
from mininet.node import RemoteController
from mininet.node import OVSSwitch

from mininet.term import cleanUpScreens, makeTerms
from time import time,sleep
import signal
import sys


from time import time

net = None

class InternetTopo(Topo):
    def __init__(self, n=1, **opts):
        Topo.__init__(self, **opts)

        privateHost11 = self.addHost('pri.1.2', ip='192.168.1.2/24', defaultRoute='via 192.168.1.1')
        privateHost12 = self.addHost('pri.1.3', ip='192.168.1.3/24', defaultRoute='via 192.168.1.1')
        privateHost21 = self.addHost('pri.2.2', ip='192.168.2.2/24', defaultRoute='via 192.168.2.1')
        privateHost22 = self.addHost('pri.2.3', ip='192.168.2.3/24', defaultRoute='via 192.168.2.1')

        publicHost1 = self.addHost('server', ip='10.0.0.3/24', mac='00:00:00:00:01:03', defaultRoute='via 10.0.0.254')
        publicHost2 = self.addHost('public1', ip='10.0.0.4/24', mac='00:00:00:00:01:04', defaultRoute='via 10.0.0.254')
        natSwitch1 = self.addSwitch('nat1', dpid='1')
        natSwitch2 = self.addSwitch('nat2', dpid='2')
        publicSwitch1 = self.addSwitch('s1', dpid="10")

        self.addLink(publicSwitch1, natSwitch1, 2, 1)
        self.addLink(publicSwitch1, natSwitch2, 3, 1)
        self.addLink(publicSwitch1, publicHost1, 4, 1)
        self.addLink(publicSwitch1, publicHost2, 5, 1)

        self.addLink(privateHost11, natSwitch1, 1, 2)
        self.addLink(privateHost12, natSwitch1, 1, 3)
        self.addLink(privateHost21, natSwitch2, 1, 2)
        self.addLink(privateHost22, natSwitch2, 1, 3)
            
def hostTerm(net):
    "Start a terminal for each node."
    if 'DISPLAY' not in os.environ:
        error( "Error starting terms: Cannot connect to display\n" )
        return
    info( "*** Running terms on %s\n" % os.environ[ 'DISPLAY' ] )
    cleanUpScreens()
    terms = []
    net.terms += makeTerms( net.hosts, 'host' )

def sigint_handler(signum, frame):
    global net
    net.stop()
    Cleanup.cleanup()
    sys.exit()

def run():
    "Create network and run the CLI"
    topo = InternetTopo()
    global net
    net = Mininet(topo=topo, controller=RemoteController('c0'))
    net.start()
    for s in net.switches:
        print(s.connected())

    #net.pingAll()

    print('^^^^^^^^^ TEST START ^^^^^^^^^^')

    for host in net.hosts:
        if host.name == "server":
            externServ = host

    hostTerm(net)

    sleep(600)  #maximum time until automatically exit

    net.stop()



if __name__ == '__main__':
    setLogLevel('info')
    signal.signal(signal.SIGINT, sigint_handler)
    run()
