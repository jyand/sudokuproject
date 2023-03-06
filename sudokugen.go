package main

import (
        //"bufio"
        //"fmt"
        "math/rand"
        "os"
        "strconv"
        "time"
)

const SIZE int = 9

func GenerateBoard() []string {
        var s []string
        for k := 0 ; k < SIZE ; k++ {
        rand.Seed(time.Now().UnixNano())
                var str string
                for j := 0 ; j < SIZE - 1 ; j++ {
                        r := int64(rand.Intn(SIZE))
                        str += strconv.FormatInt(r, 10) + " "
                }
                r := int64(rand.Intn(SIZE))
                str += strconv.FormatInt(r, 10)
                s = append(s, str)
        }
        return s
}

func FileFromStrings(fname string, s []string) {
        f, _ := os.Create(fname)
        defer f.Close()
        for _, u := range s {
                f.Write([]byte(u))
                f.WriteString("\n")
        }
}

func main() {
        s := GenerateBoard()
        FileFromStrings("input.txt", s)
} 
