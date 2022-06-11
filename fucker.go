package main

import (
	"fmt"
	"log"

	"github.com/hashicorp/mdns"
)

var addr string

func fuck() {
	fmt.Println(addr)
}

func main() {
	entriesCh := make(chan *mdns.ServiceEntry, 4)
	go func() {
		for entry := range entriesCh {
			//fmt.Printf("Got new entry: %+v\n", entry)
			addr = entry.AddrV4.String()
			fuck()
		}
	}()

	//mdns.Lookup("fucker._http._tcp", entriesCh)
	cfg := &mdns.QueryParam{
		Service:     "fucker._http._tcp",
		DisableIPv6: true,
		Entries:     entriesCh,
	}
	err := mdns.Query(cfg)
	if err != nil {
		log.Println(err)
	}
	close(entriesCh)
}
